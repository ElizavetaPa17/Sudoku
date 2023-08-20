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

    void free();
    bool loadFromFile(SDL_Renderer* renderer, const std::string& path);

    void render(SDL_Renderer* renderer, int x, int y, const SDL_Rect* clip = nullptr,
                double angle = 0.0, const SDL_Point* rotating_center = nullptr);

    void setAlpha(Uint8 alpha);

    int getWidth()  const noexcept { return width_;  }
    int getHeight() const noexcept { return height_; }
    SDL_Point getPosition() const noexcept { return position_; }

private:
    SDL_Texture* texture_;

    int width_;
    int height_;
    SDL_Point position_; // the position is a top left point
};
