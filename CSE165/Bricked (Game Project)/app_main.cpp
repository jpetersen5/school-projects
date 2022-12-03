#include <iostream>
#include <SFML/Graphics.hpp>

#include "game.h"

int main() {
    // initialize window
    sf::ContextSettings settings; // openGL settings for window
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Bricked", sf::Style::Default, settings);
    window.setFramerateLimit(60); // changes speed of the game, updates happen per frame
    window.setKeyRepeatEnabled(false); // fixes holding down movement keys

    Game brickgame = Game(window);

    // event loop
    while (window.isOpen()) {
        sf::Event event;
        // process events from event queue
        // handles however many events happen in a single frame before updating
        while (window.pollEvent(event)) {
            brickgame.happen(event);
        } 

        brickgame.update(); // update per frame
    }

	return 0;
}