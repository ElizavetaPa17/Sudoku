#include "STexture.h"

STexture::STexture() : texture_(nullptr), width_(0), height_(0), position_(0, 0)
{    
}

STexture::~STexture() {
    free();
}

STexture::STexture(STexture&& another_texture) noexcept {
    *this = std::move(another_texture);
}

STexture& STexture::operator=(STexture && another_texture) noexcept {
    free();

    if (this == &another_texture) {
        return *this;
    }

    texture_  = another_texture.texture_;
    width_    = another_texture.width_;
    height_   = another_texture.height_;
    position_ = another_texture.position_;

    // free resource and set default value
    another_texture.texture_ = nullptr;
    another_texture.width_ = another_texture.height_ = 0;
    another_texture.position_ = { 0, 0 };

    return *this;
}

void STexture::free() {
    if (texture_) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

bool STexture::loadFromFile(SDL_Renderer *renderer, const std::string& path) {
    // get rid of preexisting texture
    free();

    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (!loaded_surface) {
        std::cerr << "Unable to load surface from file. Path: " << path 
                  << ". IMG_Error " << IMG_GetError() << '\n';
        return false;
    }

    // removing background. color key is transparent key.
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0xFF, 0xFF));
    
    texture_ = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (!texture_) {
        std::cerr << "Unable to create texture from surface. SDL_Error: " << SDL_GetError() << '\n';
        return false;
    }

    width_  = loaded_surface->w;
    height_ = loaded_surface->h;

    SDL_FreeSurface(loaded_surface);
    return true;
}

void STexture::render(SDL_Renderer* renderer, int x, int y, const SDL_Rect* clip, 
                      double angle, const SDL_Point* rotating_center) 
{
    SDL_Rect render_quad = { x, y, width_, height_ };
    if (clip) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture_, clip, &render_quad, angle, rotating_center, SDL_FLIP_NONE);
}

void STexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture_, alpha);
}
