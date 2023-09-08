#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../resources/constants.h"
#include "../handle_elements/SBoard.h"
#include "../handle_elements/SChunkPlayer.h"
#include "../renderer/STexture.h"
#include "SScoreLabel.h"
#include "STimerLabel.h"
#include "SGameLevelLabel.h"
#include "SExitGameDialog.h"
#include "SWidget.h"
#include "SButton.h"
#include "SRulesButton.h"

class SGameEnvironment : public SWidget {
public:
    SGameEnvironment() = default;

    void handleChildEvent(SWidget* child) override;
    void sendParentEvent() override;

    // must be set up before using
    void setUp(SWidget* parent, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void handleEvents(SDL_Event& event);

    void reset();
    int  getPastTicks();

    void setGameLevel(SDL_Renderer* renderer, SConstants::GameLevel game_level);
    
    SConstants::GameState getGameState();

    void setScore(SDL_Renderer* renderer, int value);
    int  getScore();

private:
   SBoard board_;
   SExitGameDialog exit_game_dialog_;
   
   SScoreLabel score_label_;
   STimerLabel timer_label_;
   SGameLevelLabel game_level_label_;

   SButton voice_button_;
   SRulesButton rules_button_;
   SButton opened_hint_button_;
   SButton closed_hint_button_;
   SButton quit_game_button_;

   bool is_opened_hint_ = false;
   bool displ_exit_dialog_ = false;

   SConstants::GameState game_state_ = SConstants::GameState::PLAY;
};
