#pragma once

#include <SDL2/SDL.h>

#include "../renderer/STexture.h"
#include "SWidget.h"

class SButton : public SWidget {
public:
    SButton() = default;

    void handleChildEvent(SWidget* child) override;
    void sendParentEvent() override;

    // must be set up before using
    virtual void setUp(SWidget* parent, const STexture& background_texture);
    virtual void handleEvents(SDL_Event& event);
    virtual void render(SDL_Renderer* renderer);

    // the position is the top left point. it assigns background position.
    // text position calculate with offset
    virtual void setPosition(SDL_Point position);
protected:
    STexture _background_texture;
};
