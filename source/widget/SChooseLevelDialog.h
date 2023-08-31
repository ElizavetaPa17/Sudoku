#pragma once

#include <SDL2/SDL.h>

#include "SButton.h"
#include "SWidget.h"
#include "../renderer/SFont.h"
#include "../resources/constants.h"

class SChooseLevelDialog : public SWidget {
public:
    SChooseLevelDialog() = default;
    
    void handleChildEvent(SWidget *child) override;
    void sendParentEvent() override;

    // must be setUp before using
    void setUp(SWidget* parent, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void handleEvents(SDL_Event& event);

    void setPosition(SDL_Point position);
    typename SConstants::GameLevel getGameLevel();

private:
    STexture background_texture_;
    SButton  easy_level_button_;
    SButton  middle_level_button_;
    SButton  hard_level_button_;

    typename SConstants::GameLevel game_level_ = SConstants::GameLevel::NOT_SELECTED;
};
