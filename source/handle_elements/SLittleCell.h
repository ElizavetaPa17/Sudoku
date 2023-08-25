#pragma once

#include "../renderer/STexture.h"
#include "SCellFlyweight.h"

class SLittleCell final {
public:
    SLittleCell();
    SLittleCell(const STexture& background, char value);

    void handleEvents(SDL_Event& event);
    void render(SDL_Renderer* renderer);
    void setTexture(const STexture& texture);

    void setPosition(SDL_Point position) noexcept { background_.setPosition(position); }
    SDL_Point getPosition() const noexcept { return background_.getPosition(); }
    
    void setValue(char value) noexcept;
    int getValue() const noexcept { return value_; }

    int getWidth()  const noexcept { return background_.getWidth(); }
    int getHeight() const noexcept { return background_.getHeight(); }

    void setActive(bool is_active) noexcept { is_active_ = is_active; }
    bool isActive() const noexcept { return is_active_; }

    bool isValid() const; // SLittleCell is valid if it has the background
private:
    // texture keeps cell width, height and position
    STexture background_;

    STexture* value_ptr_; // pointer to static memory from SCellFlyweight (needn't to be deleted!)

    char value_;
    bool is_active_;
};

