#pragma once

#include <SDL2/SDL.h>

#include "../renderer/STexture.h"

class SButton final {
public:
    SButton(STexture& background, STexture& text);
    ~SButton() = default;

    SButton(const SButton&) = default;
    SButton& operator=(const SButton&) = default;
    
    SButton(SButton&&) = default;
    SButton& operator=(SButton&&) = default;

    void handleEvents(SDL_Event& event);
    void render(SDL_Renderer* renderer);

    // the position is the top left point. it assigns background position.
    // text position calculate with offset
    void setPosition(SDL_Point position);
    SDL_Point getPosition() const { return background_.getPosition(); }

    // assume that background_ is bigger than text
    int getWidth() const  { return background_.getWidth(); }
    int getHeight() const { return background_.getHeight(); }

private:
    STexture background_;
    STexture text_;
};
