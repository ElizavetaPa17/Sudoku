#include "SFont.h"

SFont::SFont() : font_(nullptr)
{
}

SFont::SFont(const SFont& font) {
    *this = font;
}

SFont& SFont::operator=(const SFont& font) {
    if (this == &font) {
        return *this;
    }

    font_ = font.font_;
    path_ = font.path_;

    return *this;
}

SFont::SFont(SFont&& another_font) noexcept {
    *this = std::move(another_font);
}

SFont& SFont::operator=(SFont&& another_font) noexcept {
    if (this == &another_font) {
        return *this;
    }

    font_ = std::move(another_font.font_);
    path_ = std::move(another_font.path_);

    return *this;
}

bool SFont::loadFromFile(const std::string& path, int font_size) {
    font_.reset(TTF_OpenFont(path.c_str(), font_size), Deleter());
    if (!font_) {
        std::cerr << "Unable to open file to load font. Path: " << path 
                  << ". TTF_Error: " << TTF_GetError() << '\n';
        path_  = "";
        return false;
    }

    path_ = path;
    return true;
}

// the caller function is responsible for the checking if the return texture is valid
STexture SFont::createFontTexture(SDL_Renderer *renderer, const std::string& text, SDL_Color color) {
    if (!font_) {
        std::cerr << "The font is empty. Unable to create texture.\n";
        return STexture();
    }

    SDL_Surface* text_surface = TTF_RenderText_Solid(font_.get(), text.c_str(), color);
    if (!text_surface) {
        std::cerr << "Unable to create text_surface from font. TTF_Error: " << TTF_GetError() << '\n';
        return STexture();
    } else {
        STexture texture;
        texture.createTextureFromSurface(renderer, text_surface);

        SDL_FreeSurface(text_surface);
        return texture;
    }
}

