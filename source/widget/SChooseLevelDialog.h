#pragma once

#include <SDL2/SDL.h>

#include "SButton.h"
#include "../renderer/SFont.h"
#include "../resources/constants.h"

class SChooseLevelDialog final {
public:
    SChooseLevelDialog() = default;
    
    // must be setUp before using
    void setUp(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void setPosition(SDL_Point position);

private:
    STexture background_texture_;
    SButton  easy_level_button_;
    SButton  middle_level_button_;
    SButton  hard_level_button_;
};
