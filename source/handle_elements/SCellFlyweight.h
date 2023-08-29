#pragma once

#include <SDL2/SDL.h>

#include "SLittleCell.h"
#include "../renderer/SFont.h"
#include "../resources/constants.h"

class SCellFlyweight final {
public:
    // before using the instance must be initialized
    static bool init(SDL_Renderer* renderer);
    static STexture* getFlyweightValue(char value);

private:
    SCellFlyweight() = default;

    static STexture shared_cells_[SConstants::SHARED_CELL_VALUE_COUNT];
};
