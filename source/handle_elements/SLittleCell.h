#pragma once

#include "../renderer/STexture.h"
#include "SCellFlyweight.h"

const int CELL_OFFSET = 5; // rendering offset (to render the value in the center of each cell)

class SLittleCell final {
public:
    SLittleCell();

    void handleEvents(SDL_Event& event);
    void render(SDL_Renderer* renderer);

    void setPosition(SDL_Point position) noexcept { position_ = position; }
    SDL_Point getPosition() const noexcept { return position_; }
    
    void setValue(char value) noexcept;
    int getValue() const noexcept { return value_; }

   // void setActive(bool is_active) noexcept { is_active_ = is_active; }
   // bool isActive() const noexcept { return is_active_; }

   // bool isValid() const; // SLittleCell is valid if it has the background
private:
    // texture keeps cell width, height and position
    STexture* value_ptr_; // pointer to static memory from SCellFlyweight (needn't to be deleted!)

    SDL_Point position_;
    char value_;
};

