#pragma once

#include <SDL2/SDL.h>

#include "SButton.h"
#include "SWidget.h"
#include "../handle_elements/SMusicPlayer.h"
#include "../resources/constants.h"

class SVoiceButton : public SButton {
public:
    SVoiceButton() = default;

    void setUp(SWidget* parent, 
               const STexture& background_texture,
               const STexture& stop_background_texture, 
               const SChunkPlayer& chunk_player, 
               const SMusicPlayer& music_player);

    void handleEvents(SDL_Event& event) override;
    void render(SDL_Renderer* renderer) override;
    void setPosition(SDL_Point position) override;

private:
    using SButton::setUp; // hide base class method
    
    STexture stop_background_texture_;
    SMusicPlayer music_player_;
};
