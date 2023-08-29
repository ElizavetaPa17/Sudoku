#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "STexture.h"

class SFont final {
public:
    struct Deleter {
        void operator()(TTF_Font* font) const {
            TTF_CloseFont(font);
        }
    };

    SFont();
    SFont(const std::string& path, int font_size);
    ~SFont() = default; // shared_ptr and deleter are responsible for the font deleting

    SFont(const SFont&);
    SFont& operator=(const SFont&);

    SFont(SFont&&) noexcept;
    SFont& operator=(SFont&&) noexcept;

    bool loadFromFile(const std::string& path, int font_size);

    STexture createFontTexture(SDL_Renderer* renderer, const std::string& text, SDL_Color);

    const std::string& getPath() const noexcept { return path_; }
private:
    std::shared_ptr<TTF_Font> font_;
    std::string path_;
};
