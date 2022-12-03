#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "game.h"
#include "object.h"
#include "player.h"

using namespace sf;

// creates a game instance, defaults to state 2 (start screen)
Game::Game(RenderWindow& window) : window(window), state(2), level(objects) {
    // load font for ingame text
    if (font.loadFromFile("bin/kindergarten.ttf")) 
        std:: cout << "Font load successful" << std::endl;
    printToScreen("BRICKED", WINDOW_W/2, WINDOW_H/4, 80, BRICK_COLOR);
    printToScreen("Press SPACE to start...", WINDOW_W/2, WINDOW_H/2, 28, BRICK_COLOR);
}

// destructor frees up all objects memory
Game::~Game() {
    for (Object* object : objects)
        delete object;
}

// event handler to process the event queue
// inputs: event        an SFML object representing an action that happened
void Game::happen(Event& event) {
    // close on close. duh
    if (event.type == Event::Closed)
        window.close();
    
    // check for key presses
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key& key = event.key.code;
        // check for movement keypresses
        if (state == 1 && (key == sf::Keyboard::A || key == sf::Keyboard::D || 
            key == sf::Keyboard::Left || key == sf::Keyboard::Right))
            // send to Player object to handle controls
            dynamic_cast<Player*>(paddle)->controls(key);
        else if (state == 2 && key == sf::Keyboard::Space)
            newLevel();
        // pause on ESC
        else if (key == sf::Keyboard::Escape)
            pause();
    }
    else if (event.type == sf::Event::KeyReleased) {
        sf::Keyboard::Key& key = event.key.code;
        // allows player to hold down movement keys, stops when key is released
        // NEEDS FIXING: if player overlaps key presses, releasing any movement key
        // will stop the paddle
        if (state == 1 && (key == sf::Keyboard::A || key == sf::Keyboard::D || 
            key == sf::Keyboard::Left || key == sf::Keyboard::Right))
            dynamic_cast<Player*>(paddle)->releaseControls();
    }
}

// allows gameplay to pause
// game state determines how updates happen; 2 is start screen, 1 is in play, 0 is paused
void Game::pause() {
    if (state == 1) {
        printToScreen("PAUSED", WINDOW_W/2, WINDOW_H/3, 180, BRICK_COLOR);
        state = 0;
    } else if (!state) {
        texts.pop_back();
        state = 1;
    }
}

// wipes all text on screen for moving between screens (i.e. start screen to in-play)
void Game::clearText() {
    while (texts.size() > 0) texts.pop_back();
}

// handles frame-to-frame updates
void Game::update() {
    // wipe screen to prepare for drawing game
    window.clear(BG_COLOR);
    // draw texts first
    for (Text text : texts) window.draw(text);
    // paddle exists in-play and paused, but not start screen
    if (state != 2) {
        paddle->draw(window);
        if (state == 1) paddle->advance(); // paddle only moves in-play
    }
    // iterator to draw all bricks and ball
    for (auto i = objects.begin(); i != objects.end(); i++) {
        Object* curObj = *i;
        // handle brick deletion
        if (curObj->toDel) {
            delete curObj;
            i = objects.erase(i);
            --i;
            continue;
        }
        curObj->draw(window);
        // in-play, move objects if moveable
        if (state == 1) curObj->advance();
    }
    window.display();
}

// begin generation of a new level
// CURRENTLY only creates the only level; possibility for more or custom levels exists
void Game::newLevel() {
    // set correct state (playing)
    state = 1;
    // clear game screen
    clearText();
    // iterator to clear last level objects
    for (auto i = objects.end(); objects.size() > 0; --i) {
        delete *i;
        objects.pop_back();
    }
    // add info to top of screen
    printToScreen("Jason Petersen", 120, 10, 28, WIN_COLOR);
    printToScreen(" l ", 2*WINDOW_W/7, 10, 28, BRICK_COLOR);
    printToScreen("BRICKED", WINDOW_W/2, 10, 28, BRICK_COLOR);
    printToScreen(" l ", 5*WINDOW_W/7, 10, 28, BRICK_COLOR);
    printToScreen("Ver " + GAME_VER, WINDOW_W-80, 10, 28, WIN_COLOR);
    // generate level
    level.build();
    // add player paddle and ball
    paddle = new Player(*this);
    objects.push_back(new Ball(*this, 0.5, -5, WINDOW_W/2, WINDOW_H/2));
}  

// handles SFML Text objects to generate on screen text
// inputs: str          text to display
//         xpos,ypos    positioning of text (centered)
//         size         size of text in point
//         color        color to display text in
void Game::printToScreen(std::string str, int xpos, int ypos, int size, Color color) {
    // create a text object to print
    Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    // calculate text size to center xpos
    FloatRect textsize = text.getGlobalBounds();
    xpos -= textsize.width/2;
    text.setPosition(xpos,ypos);
    // add to text list for update to handle drawing
    texts.push_back(text);
}

// returns reference to objects vector
std::vector<Object*>& Game::objectsVec() {
    return objects;
}

// returns pointer to game's player (paddle)
Object* Game::getPaddle() const {
    return paddle;
}