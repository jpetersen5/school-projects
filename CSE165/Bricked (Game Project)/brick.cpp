#include <math.h>

#include "brick.h"

// brick object position determined by level builder
Brick::Brick(float xpos, float ypos) : brickRect(sf::Vector2f(BRICK_W, BRICK_H)) {
    brickRect.setPosition(xpos,ypos);
    brickRect.setFillColor(BRICK_COLOR);
}

// draws brick object
void Brick::draw(sf::RenderWindow& window) const {
    window.draw(brickRect);
}

// returns the shape held by the brick object
sf::RectangleShape Brick::getBrick() {
    return brickRect;
}