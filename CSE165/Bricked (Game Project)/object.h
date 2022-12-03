#ifndef BRICKGAME_OBJECT_H
#define BRICKGAME_OBJECT_H

#include <SFML/Graphics/RenderWindow.hpp>

// base class used for all objects in-game; pure virtual
class Object {
    public:
    virtual ~Object() = default;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void advance() {};
    bool toDel = false;
};

#endif