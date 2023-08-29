#pragma once

#include <SDL2/SDL.h>

#include "../renderer/STexture.h"
#include "../renderer/SFont.h"
#include "../handle_elements/STimer.h"
#include "../resources/constants.h"

class STimerLabel final {
public:
    STimerLabel() = default;

    void render(SDL_Renderer* renderer);
    void setUp(SDL_Renderer* renderer, const STexture& background_texture);

    // assume that label position is background position
    void setPosition(SDL_Point position);

    void startTimer();
    void stopTimer();
    void pauseTimer();
    void unpauseTimer();

private:
    void updateTimer(SDL_Renderer* renderer);
    STexture convertTicks(SDL_Renderer* renderer);

    STexture background_texture_;
    STexture timer_texture_;
    SFont font_;

    STimer   timer_;
};
