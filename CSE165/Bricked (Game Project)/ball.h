#ifndef BRICKGAME_BALL_H
#define BRICKGAME_BALL_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "const.h"
#include "game.h"
#include "object.h"

// Ball object exists as the game's main object alongside the Player
// holds speed vector to determine where to move the ball per frame
class Ball : public Object {
    public:
    Ball(Game& game, float xspeed, float yspeed, float xpos, float ypos);
    void draw(sf::RenderWindow& window) const;
    void newSpeed(const sf::Vector2f& vel);
    void advance();

    private:
    Game& curGame;
    sf::Vector2f speed;
    sf::CircleShape ballShape;

    void wallCollision(const sf::FloatRect& objEdges);
    void objectCollision(const sf::FloatRect& objEdges);
    void cornerCollide(float x, float y);
};

#endif //BRICKGAME_BALL_H