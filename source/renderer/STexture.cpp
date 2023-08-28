#include "STexture.h"

STexture::STexture() : texture_(nullptr), width_(0), height_(0)
{    
    position_ = { 0, 0 };
}

STexture::STexture(const STexture& another_texture) {
    *this = another_texture;
}

STexture& STexture::operator=(const STexture& another_texture) {
    if (this == &another_texture) {
        return *this;
    }

    texture_  = another_texture.texture_;
    width_    = another_texture.width_;
    height_   = another_texture.height_;
    position_ = another_texture.position_; 

    return *this;
}

STexture::STexture(STexture&& another_texture) noexcept {
    *this = std::move(another_texture);
}

STexture& STexture::operator=(STexture && another_texture) noexcept {
    if (this == &another_texture) {
        return *this;
    }

    texture_  = std::move(another_texture.texture_);
    width_    = another_texture.width_;
    height_   = another_texture.height_;
    position_ = another_texture.position_;

    // set default value
    another_texture.setDefault();

    return *this;
}

// free the texture with reseting members
void STexture::setDefault() {
    width_  = 0;
    height_ = 0;
    position_ = { 0, 0 };
}

bool STexture::loadFromFile(SDL_Renderer *renderer, const std::string& path) {
    setDefault();

    bool success = false;
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (!loaded_surface) {
        std::cerr << "Unable to load surface from file. Path: " << path 
                  << ". IMG_Error " << IMG_GetError() << '\n';
        return success;
    } else {
        // removing background. color key is transparent key.
       // SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0xFF, 0xFF));
    
        if (createTextureFromSurface(renderer, loaded_surface)) {
            success = true;
        }

        SDL_FreeSurface(loaded_surface);
    }

    return success;
}

// the function isn't responsible for the destroing the surface
bool STexture::createTextureFromSurface(SDL_Renderer *renderer, SDL_Surface *surface) {
    setDefault();

    texture_.reset(SDL_CreateTextureFromSurface(renderer, surface), Deleter());
    if (!texture_) {
        std::cerr << "Unable to create texture from surface. SDL_Error: " << SDL_GetError() << '\n';
        return false;
    } else {
        width_  = surface->w;
        height_ = surface->h;

        return true;
    }
}

void STexture::setTexture(std::shared_ptr<SDL_Texture>& texture) {
    texture_ = texture;
    // getting the information about new texture;
    SDL_QueryTexture(texture_.get(), nullptr, nullptr, &width_, &height_);
}

// the object must contain valid pointer in order of optimization. so the checking isn't provided.
void STexture::render(SDL_Renderer* renderer, const SDL_Rect* clip, 
                      double angle, const SDL_Point* rotating_center) 
{
    SDL_Rect render_quad = { position_.x, position_.y, width_, height_ };
    if (clip) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture_.get(), clip, &render_quad, angle, rotating_center, SDL_FLIP_NONE);
}

void STexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture_.get(), alpha);
}
