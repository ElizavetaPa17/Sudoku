#pragma once

#include <SDL2/SDL.h>

#include "../renderer/STexture.h"
#include "SWidget.h"

class SButton : public SWidget {
public:
    SButton() = default;
    SButton(const STexture& background);
    ~SButton() = default;

    SButton(const SButton&) = default;
    SButton& operator=(const SButton&) = default;
    
    SButton(SButton&&) = default;
    SButton& operator=(SButton&&) = default;

    void handleChildEvent(SWidget* child) override;
    void sendParentEvent() override;

    // must be set up before using
    void setUp(SWidget* parent, const STexture& background);
    void handleEvents(SDL_Event& event);
    void render(SDL_Renderer* renderer);

    // the position is the top left point. it assigns background position.
    // text position calculate with offset
    void setPosition(SDL_Point position);
private:
    STexture background_texture;
};
