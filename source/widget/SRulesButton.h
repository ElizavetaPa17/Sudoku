#pragma once

#include <SDL2/SDL.h>

#include "SButton.h"
#include "SWidget.h"
#include "../resources/constants.h"

class SRulesButton : public SButton {
public:
    SRulesButton() = default;

    void setUp(SWidget* parent, const STexture& background_texture, const STexture& rules_hint_texture, 
                                const SChunkPlayer& chunk_player);
    void handleEvents(SDL_Event& event) override;
    void render(SDL_Renderer* renderer) override;

    void setPosition(SDL_Point position) override;

private:
    using SButton::setUp; // hide base class method

    void openRulePage();

    STexture _rules_hint_texture;

    bool _render_hint_menu = false;
};
