#include "SCellFlyweight.h"

STexture SCellFlyweight::shared_cells_[SConstants::SHARED_CELL_VALUE_COUNT] = {};

bool SCellFlyweight::init(SDL_Renderer* renderer) {
    SFont font;
    if (!font.loadFromFile("font/test_font.ttf", 30)) {
        return false;
    }
    
    SDL_Color color = { SConstants::FONT_COLOR };

    for (int i = 0; i < SConstants::SHARED_CELL_VALUE_COUNT - 1; ++i) {
        shared_cells_[i] = font.createFontTexture(renderer, std::string(1, '0' + i), color);
    }

    shared_cells_[SConstants::SHARED_CELL_VALUE_COUNT- 1] = font.createFontTexture(renderer, " ", color);
    
    return true;
}

STexture* SCellFlyweight::getFlyweightValue(char value) { 
    if (value == ' ' ) {
        return &shared_cells_[SConstants::SHARED_CELL_VALUE_COUNT - 1];
    } else {
        if (value < 49 || value > 57) {
            std::cerr << "SCellFlyweight undefined value: " << value << '\n';
            return nullptr;
        }

        return &shared_cells_[value - 48];
    }
}
