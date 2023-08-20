#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "STexture.h"

class SFont final {
public:
    SFont();
    ~SFont();

    SFont(const SFont&) = delete;
    SFont& operator=(const SFont&) = delete;

    SFont(SFont&&) noexcept;
    SFont& operator=(SFont&&) noexcept;

    void free();
    bool loadFromFile(const std::string& path, int font_size);

    STexture createFontTexture(SDL_Renderer* renderer, const std::string& text, SDL_Color);

    const std::string& getPath() const noexcept { return path_; }
private:
    TTF_Font* font_;
    std::string path_;
};
