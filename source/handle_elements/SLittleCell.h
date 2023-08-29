#pragma once

#include "../renderer/STexture.h"
#include "SCellFlyweight.h"

const int CELL_OFFSET_X = 14; // rendering offset (to render the value in the center of each cell)
const int CELL_OFFSET_Y = 4;

class SLittleCell final {
public:
    SLittleCell();

    void handleEvents(SDL_Event& event);
    void render(SDL_Renderer* renderer);

    void setPosition(SDL_Point position) noexcept { position_ = position; }
    SDL_Point getPosition() const noexcept { return position_; }
    
    void setValue(char value) noexcept;
    int getValue() const noexcept { return value_; }

private:
    // texture keeps cell width, height and position
    STexture* value_ptr_; // pointer to static memory from SCellFlyweight (needn't to be deleted!)

    SDL_Point position_;
    char value_;
};

