#ifndef BRICKGAME_LEVELGEN_H
#define BRICKGAME_LEVELGEN_H

#include "brick.h"

// builds game level and populates objects vector with bricks
class LevelGen {
    public:
    LevelGen(std::vector<Object*>& objects);

    void build();

    private:
    std::vector<Object*>& objects;
};

#endif // BRICKGAME_LEVELGEN_H