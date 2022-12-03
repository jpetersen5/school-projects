#ifndef BRICKGAME_BRICK_H
#define BRICKGAME_BRICK_H

#include <SFML/Graphics/RectangleShape.hpp>

#include "const.h"
#include "object.h"

// simple object that holds a rectangle and it's position
// primary objective of the game
class Brick : public Object {
    public:
    Brick(float xpos, float ypos);
    void draw(sf::RenderWindow& window) const;
    sf::RectangleShape getBrick();

    private:
    sf::RectangleShape brickRect;
};

#endif // BRICKGAME_BRICK_H