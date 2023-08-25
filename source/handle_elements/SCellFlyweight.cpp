#include "SCellFlyweight.h"

#include "../renderer/SFont.h"

STexture SCellFlyweight::shared_cells_[SHARED_VALUE_COUNT] = {};

bool SCellFlyweight::init(SDL_Renderer* renderer) {
    SFont font;
    if (!font.loadFromFile("font/test_font.ttf", 30)) {
        return false;
    }
    
    SDL_Color color = { 0x00, 0x00, 0xFF };

    for (int i = 0; i < SHARED_VALUE_COUNT - 1; ++i) { // SHARED_VALUE_COUNT equals 11 so the cast is safe
        shared_cells_[i] = font.createFontTexture(renderer, std::string(1, '0' + i), color);
    }

    shared_cells_[SHARED_VALUE_COUNT - 1] = font.createFontTexture(renderer, " ", color);
    
    return true;
}

STexture* SCellFlyweight::getFlyweightValue(char value) { 
    if (value == ' ' ) {
        return &shared_cells_[SHARED_VALUE_COUNT - 1];
    } else {
        std::cerr << value << '\n';
        return &shared_cells_[value - 48];
    }
}
