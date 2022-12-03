#ifndef BRICKGAME_GAME_H
#define BRICKGAME_GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "const.h"
#include "object.h"
#include "levelgen.h"

// instance of game 
// handles important gameplay loop such as updating per frame, events from event queue, etc.
class Game {
    public:
    // construct game board in window
    Game(sf::RenderWindow& window);
    ~Game();

    // redraw game with updated values
    void update();
    // react based on what event is parsed (key press, etc.)
    void happen(sf::Event& event);
    std::vector<Object*>& objectsVec();
    Object* getPaddle() const;

    private:
    sf::RenderWindow& window;
    // holds current game state; 0 for paused, 1 for in progress
    int state;
    sf::Font font; // loaded font for ingame text
    std::vector<Object*> objects;
    Object* paddle; // player object
    std::vector<sf::Text> texts;
    LevelGen level;

    void pause();
    void clear();
    void clearText();
    void printToScreen(std::string str, int xpos, int ypos, int size = 28, sf::Color color = MAIN_COLOR);
    void newLevel();
    void gameOver(bool win = false);

};

#endif // BRICKGAME_RUNNER_H