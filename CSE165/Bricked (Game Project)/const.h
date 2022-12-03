#ifndef BRICKGAME_CONST_H
#define BRICKGAME_CONST_H

#include <SFML/Graphics/RenderWindow.hpp>

// game version
const std::string GAME_VER = "0.1.0";

// default window size 720p
const unsigned int WINDOW_W = 1280;
const unsigned int WINDOW_H = 720;

// paddle constants
const float PADDLE_W = 100;
const float PADDLE_H = 10;
const float PADDLE_ACC = 1; // accelleration

// ball constants
const float BALL_R = 8; // radius
const float BALL_MAXSPEED = 6.0;

// brick constants
const float BRICK_SIZE = 3; // scalar to shape entire brick size
const float BRICK_W = 10 * BRICK_SIZE;
const float BRICK_H = 5 * BRICK_SIZE;
const float BRICK_SEP = 2 * BRICK_SIZE; // seperation
const unsigned int BRICKS_PER_LINE = WINDOW_W / int(BRICK_W + BRICK_SEP) - 1;
const unsigned int BRICK_LINES = 5;

// angle constant
const float RAD_TO_DEG = 57.295779513f;

// color constants
const sf::Color MAIN_COLOR = sf::Color(190,190,190);
const sf::Color BG_COLOR = sf::Color(10,10,10);
const sf::Color BRICK_COLOR = sf::Color(188,74,60);
const sf::Color BALL_COLOR = sf::Color(222,222,222);
const sf::Color LOSE_COLOR = sf::Color(206,18,38);
const sf::Color WIN_COLOR = sf::Color(86,189,0);

#endif // BRICKGAME_CONST_H