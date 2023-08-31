#pragma once
#include <SDL2/SDL.h>

namespace SConstants {
    constexpr int SCREEN_WIDTH  = 736;
    constexpr int SCREEN_HEIGHT = 474;
    
    constexpr int CELL_DIMEN = 9;
    constexpr int CELL_COUNT = CELL_DIMEN * CELL_DIMEN;

    constexpr int SHARED_CELL_VALUE_COUNT = 11; // from 0 to 9 and space

    constexpr int TIMER_VALUE_OFFSET_X = 145;
    constexpr int TIMER_VALUE_OFFSET_Y = 5;

    constexpr int SCORE_VALUE_OFFSET_X = 150;
    constexpr int SCORE_VALUE_OFFSET_Y = 0;

    constexpr SDL_Color FONT_COLOR = { 0x42, 0x25, 0x15 };

    enum class GameLevel {
        EASY_LEVEL,
        MIDDLE_LEVEL,
        HARD_LEVEL,
        NOT_SELECTED,
    };
}
