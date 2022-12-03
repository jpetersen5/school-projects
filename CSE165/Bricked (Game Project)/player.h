#ifndef BRICKGAME_PLAYER_H
#define BRICKGAME_PLAYER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "ball.h"
#include "const.h"
#include "game.h"
#include "object.h"

// player object, controlled by key presses and main object in the game alongside ball
class Player : public Object {
    public:
    Player(Game& game);
    void draw(sf::RenderWindow& window) const;
    void advance();
    const sf::Vector2f* position();
    void controls(sf::Keyboard::Key& key);
    void releaseControls();
    sf::RectangleShape getPaddle();
    float getSpeed();

    private:
    Game& curGame;
    sf::RectangleShape paddle;
    float speed;
    int direction;

};

#endif //BRICKGAME_PLAYER_H