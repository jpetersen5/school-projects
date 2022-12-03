#include <iostream>
#include <math.h>
#include <typeinfo>

#include "ball.h"
#include "player.h"

// constructor for Ball object
// inputs: game        Game instance running
//         xspeed      horizontal speed of ball at spawn
//         yspeed      vertical speed of ball at spawn
//         xpos, ypos  position
// notes: ballShape can be changed in const.h with BALL_R
//        as well as BALL_COLOR
Ball::Ball(Game& game, float xspeed, float yspeed, float xpos, float ypos) 
        : curGame(game), speed(xspeed,yspeed), ballShape(BALL_R, 40) {
    ballShape.setFillColor(BALL_COLOR);
    ballShape.setPosition(xpos,ypos);
}

// draws Ball object on-screen
void Ball::draw(sf::RenderWindow& window) const {
    window.draw(ballShape);
}

// utility function
// returns simple distance of a point using pythagorean theorem
float dist(float x, float y) {
    return sqrt(x * x + y * y);
}

// advances Ball object
void Ball::advance() {
    sf::FloatRect edge = ballShape.getGlobalBounds();
    // ensures speed doesn't exceed unmaintainable amount
    if (speed.x > BALL_MAXSPEED) speed.x = BALL_MAXSPEED;
    if (speed.y > BALL_MAXSPEED) speed.y = BALL_MAXSPEED;
    // handle any wall or object (brick / paddle) collisions
    wallCollision(edge);
    objectCollision(edge);
    // move ball by offset determined by speed
    ballShape.move(speed);
}

// handles simple collisions with walls (inverse angle of approach)
void Ball::wallCollision(const sf::FloatRect& objEdges) {
    // screen edges, slight barrier to account for game
    if (objEdges.left < 10 || objEdges.left + objEdges.width > WINDOW_W - 10)
        speed.x *= -1;
    if (objEdges.top < WINDOW_H/13) // 1/13 of height due to text at top of game
        speed.y *= -1;
    // "respawn" ball after exiting bottom of screen
    // hacky, but possibly in the future can be worked with a # of lives system
    if (objEdges.top > WINDOW_H) {
        ballShape.setPosition(WINDOW_W/2, WINDOW_H/2);
        speed.x = 0.5;
        speed.y = 4;
    }
}

// handles collisions with bricks or the paddle
void Ball::objectCollision(const sf::FloatRect& objEdges) {
    std::vector<Object*>& objects = curGame.objectsVec();
    Player* paddle = dynamic_cast<Player*>(curGame.getPaddle());

    // cycle thru objects and check for collisions
    for (uint i = 0; i < objects.size(); i++) {
        // dynamic cast for only brick types (not ball or paddle)
        if (Brick* brick = dynamic_cast<Brick*>(objects[i])) { 
            sf::FloatRect brickEdges = brick->getBrick().getGlobalBounds();
            // SFML intersect and contains functions used for collision conditions
            if (brickEdges.intersects(objEdges)) {
                // collision: left or right side
                if (brickEdges.contains(objEdges.left + objEdges.width / 2, objEdges.top)
                 || brickEdges.contains(objEdges.left + objEdges.width / 2, objEdges.top + objEdges.height))
                    speed.y *= -1; // simple inverse
                // collision: top or bottom side
                else if (brickEdges.contains(objEdges.left, objEdges.top + objEdges.height / 2)
                 || brickEdges.contains(objEdges.left + objEdges.width, objEdges.top + objEdges.height / 2))
                    speed.x *= -1; // simple inverse
                // collision: top left corner
                else if (dist(objEdges.left + objEdges.width / 2 - brickEdges.left,
                              objEdges.top + objEdges.height / 2 - brickEdges.top) < objEdges.width / 2)
                    cornerCollide(brickEdges.left,brickEdges.top);
                // collision: top right corner
                else if (dist(objEdges.left + objEdges.width / 2 - (brickEdges.left + brickEdges.width),
                              objEdges.top + objEdges.height / 2 - brickEdges.top) < objEdges.width / 2)
                    cornerCollide(brickEdges.left+brickEdges.width,brickEdges.top);
                // collision: bottom right corner
                else if (dist(objEdges.left + objEdges.width / 2 - (brickEdges.left + brickEdges.width),
                              objEdges.top + objEdges.height / 2 - (brickEdges.top + brickEdges.height)) < objEdges.width / 2)
                    cornerCollide(brickEdges.left+brickEdges.width,brickEdges.top+brickEdges.height);
                // collision: bottom left corner
                else if (dist(objEdges.left + objEdges.width / 2 - brickEdges.left,
                              objEdges.top + objEdges.height / 2 - (brickEdges.top + brickEdges.height)) < objEdges.width / 2)
                    cornerCollide(brickEdges.left,brickEdges.top+brickEdges.height);
                // set to delete next frame
                brick->toDel = true;
            }
        }
    }

    // handle paddle collisions; currently acting funky NEEDS FIXING
    // Goal: ball distance from center of paddle determines reflection angle
    // i.e. further left from origin would angle shot left, further right would angle right
    // would provide better control to player, currently has occasional strange behavior
    // most of the time it acts as a simple reflection
    sf::FloatRect paddleEdges = paddle->getPaddle().getGlobalBounds();
    if (paddleEdges.intersects(objEdges)) {
        sf::Vector2f ballPos = ballShape.getPosition();
        float paddleSpeed = paddle->getSpeed();
        float center = paddleEdges.left + paddleEdges.width/2;
        //////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////NEEDS FIXING/////////////////////////////////
        float angle = atanf((ballPos.x - center) / (ballPos.y - center)) * RAD_TO_DEG;
        //////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////
        sf::Transform rot;
        rot.rotate(angle);
        // rotation tranform determines new speed values
        speed = rot.transformPoint(speed);
        speed.y *= -1;
        rot.rotate(-2 * angle);
        speed = rot.transformPoint(speed);
        // paddle speed affects shot speed
        speed.x += paddleSpeed / 10;
        speed.y += paddleSpeed / 10;
    }
}

// handles collisions with corners of bricks
// determines distance from ball to brick to decide if corner collision is needed
// tangent used to calculate new angle
void Ball::cornerCollide(float x, float y) {
    sf::Vector2f ballPos = ballShape.getPosition();
    float angle = atanf((ballPos.x - x) / (ballPos.y - y)) * RAD_TO_DEG;
    sf::Transform rot;
    rot.rotate(angle);
    speed = rot.transformPoint(speed);
    speed.y *= -1;
    rot.rotate(-2 * angle);
    speed = rot.transformPoint(speed);
}

