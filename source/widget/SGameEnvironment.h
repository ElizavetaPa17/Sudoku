#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../handle_elements/SBoard.h"
#include "../renderer/STexture.h"
#include "../widget/SScoreLabel.h"
#include "../widget/STimerLabel.h"

class SGameEnvironment final {
public:
    SGameEnvironment() = default;

    // must be set up before using
    void setUp(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void handleEvents(SDL_Event& event);

    void startTimer();
    void stopTimer();
    void pauseTimer();
    void unpauseTimer();
    int  getPastTicks();

    void setScore(SDL_Renderer* renderer, int value);
    int  getScore();

private:
   SBoard board_;
   SScoreLabel score_label_;
   STimerLabel timer_label_;
};
