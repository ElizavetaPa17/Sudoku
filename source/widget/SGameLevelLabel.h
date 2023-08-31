#pragma once

#include <SDL2/SDL.h>

#include "../renderer/STexture.h"
#include "../resources/constants.h"

class SGameLevelLabel final {
public:
    SGameLevelLabel() = default;

    void render(SDL_Renderer* renderer);
    void setUp(SDL_Renderer* renderer, SConstants::GameLevel game_level);
    void setPosition(SDL_Point position);
      
private:
    STexture background_;
};
