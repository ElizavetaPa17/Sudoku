#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <memory>

class STexture final {
public:
    struct Deleter {
        void operator()(SDL_Texture* texture) const {
            SDL_DestroyTexture(texture);
        }
    };

    STexture();
    ~STexture() = default; // the shared_ptr and the deleter are responsible for the texture deleting

    STexture(const STexture&);
    STexture& operator=(const STexture&);
    
    STexture(STexture&&) noexcept;
    STexture& operator=(STexture&&) noexcept;

    bool loadFromFile(SDL_Renderer* renderer, const std::string& path);
    bool createTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);

    void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr,
                double angle = 0.0, const SDL_Point* rotating_center = nullptr);

    void setAlpha(Uint8 alpha);

    // if the texture pointer isn't nullptr the object is valid
    bool isValid()  const noexcept { return texture_.get(); } 
    int getWidth()  const noexcept { return width_;  }
    int getHeight() const noexcept { return height_; }

    SDL_Point getPosition() const noexcept { return position_; }
    // after the texture changing position should be set explicitly
    void setPosition(SDL_Point position) noexcept { position_ = position; }
    void setPosition(int x, int y) noexcept { position_ = { x, y }; }

private:
    void setDefault();

    std::shared_ptr<SDL_Texture> texture_;

    int width_;
    int height_;
    SDL_Point position_; // the position is a top left point
};
