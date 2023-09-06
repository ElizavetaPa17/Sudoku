#pragma once

#include <SDL2/SDL.h>

#include "SWidget.h"
#include "SButton.h"
#include "../renderer/STexture.h"
#include "../resources/constants.h"

class SExitGameDialog : public SWidget {
public:
    SExitGameDialog() = default;

    void handleChildEvent(SWidget* child) override;
    void sendParentEvent() override;

    void setUp(SWidget* parent, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void handleEvents(SDL_Event& event);

    void setPosition(SDL_Point position);
    SConstants::GameState getGameState();

private:
    STexture background_texture_;

    SButton agree_button_;
    SButton disagree_button_;

    SConstants::GameState game_state_ = SConstants::GameState::PLAY;
};
