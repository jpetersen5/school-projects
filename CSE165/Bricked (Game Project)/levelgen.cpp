#include "levelgen.h"

// takes empty vector and populates with bricks
LevelGen::LevelGen(std::vector<Object*>& objects) : objects(objects) {}

// builds brick wall
// positioning, brick number, size all determined by editable values in const.h
void LevelGen::build() {
    for (unsigned int row = 0; row < BRICK_LINES; row++) {
        for (unsigned int col = 0; col < BRICKS_PER_LINE; col++) {
            float x = (col + 1) * (BRICK_W + BRICK_SEP);
            float y = WINDOW_H/12 + (row + 1) * (BRICK_H + BRICK_SEP);
            objects.push_back(new Brick(x,y));
        }
    }
}