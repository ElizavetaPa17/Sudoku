#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class STexture final {
public:
    STexture();
    ~STexture();

    STexture(STexture&&) noexcept;
    STexture& operator=(STexture&&) noexcept;

    STexture(const STexture&)            = delete;
    STexture& operator=(const STexture&) = delete;

    bool loadFromFile(SDL_Renderer* renderer, const std::string& path);
    bool createTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);

    void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr,
                double angle = 0.0, const SDL_Point* rotating_center = nullptr);

    void setAlpha(Uint8 alpha);

    // if the texture pointer isn't nullptr the object is valid
    bool isValid()  const noexcept { return texture_; } 
    int getWidth()  const noexcept { return width_;  }
    int getHeight() const noexcept { return height_; }

    SDL_Point getPosition() const noexcept { return position_; }
    // after the texture changing position should be set explicitly
    void setPosition(SDL_Point position) noexcept { position_ = position; }

private:
    void setDefault();
    void free();

    SDL_Texture* texture_;

    int width_;
    int height_;
    SDL_Point position_; // the position is a top left point
};
