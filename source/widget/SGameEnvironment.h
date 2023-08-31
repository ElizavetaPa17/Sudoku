#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../resources/constants.h"
#include "../handle_elements/SBoard.h"
#include "../renderer/STexture.h"
#include "../widget/SScoreLabel.h"
#include "../widget/STimerLabel.h"
#include "../widget/SGameLevelLabel.h"
#include "SWidget.h"

class SGameEnvironment : public SWidget {
public:
    SGameEnvironment() = default;

    void handleChildEvent(SWidget* child) override;
    void sendParentEvent() override;

    // must be set up before using
    void setUp(SWidget* parent, SDL_Renderer* renderer);
    void setGameLevel(SDL_Renderer* renderer, SConstants::GameLevel game_level);
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
   SGameLevelLabel game_level_label_;
};
