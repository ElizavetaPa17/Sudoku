#pragma once

#include <SDL2/SDL.h>

#include "SLittleCell.h"

const int SHARED_VALUE_COUNT = 11; // there are 10 different value (from 0 to 9) + ' ' (space or empty)

class SCellFlyweight final {
public:
    // before using the instance must be initialized
    static bool init(SDL_Renderer* renderer);
    static STexture* getFlyweightValue(char value);

private:
    SCellFlyweight() = default;

    static STexture shared_cells_[SHARED_VALUE_COUNT];
};
