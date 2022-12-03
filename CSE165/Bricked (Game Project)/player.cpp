#include "player.h"

// creates a paddle relative to brick sizes
// positions paddle at the lower 8th of screen
Player::Player(Game& game) : curGame(game),
            paddle(sf::Vector2f(BRICK_SIZE * 30, BRICK_SIZE * 5)),
            speed(0), direction(0) {
    paddle.setOrigin(BRICK_SIZE * 30, 0);
    paddle.setPosition(WINDOW_W / 2, 7 * WINDOW_H / 8);
}

// draws player's paddle on-screen
void Player::draw(sf::RenderWindow& window) const {
    window.draw(paddle);
}

// moves paddle along horizontal axis, no vertical movement
void Player::advance() {
    sf::FloatRect paddleEdges = paddle.getGlobalBounds();
    // prevents paddle exiting screen
    // NEEDS FIXING: glitchy effect when intentionally trying to exceed window boundaries
    if (paddleEdges.left < 10) {
        speed = 0;
        paddle.move(10,0);
        return; // paddle can't go out of bounds
    }
    else if (paddleEdges.left + paddleEdges.width > WINDOW_W - 10) {
        speed = 0;
        paddle.move(-10,0);
        return;
    }
    // controls determine direction 
    speed += direction;
    // simulates friction, by proxy sets a speed limit
    speed -= speed / 15;
    // horizontal offset movement by speed
    paddle.move(speed, 0);
}

// A/D and Left/Right determine direction of movement
// "direction" affects speed and is set to 0 on key release so movement stops 
void Player::controls(sf::Keyboard::Key& key) {
    if (key == sf::Keyboard::A || key == sf::Keyboard::Left) 
        direction = -1;
    else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) 
        direction = 1;
}

// on release, stop accelleration
void Player::releaseControls() {
    direction = 0;
}

sf::RectangleShape Player::getPaddle() {
    return paddle;
}

float Player::getSpeed() {
    return speed;
}