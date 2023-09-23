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
      
    SConstants::GameLevel getGameLevel();
private:
    STexture background_;
    SConstants::GameLevel game_level_ = SConstants::GameLevel::NOT_SELECTED;
};
