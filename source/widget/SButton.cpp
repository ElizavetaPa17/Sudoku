#include "SButton.h"

SButton::SButton(const STexture& background, const STexture& text) 
    : background_(background), text_(text)
{   
    // assume that font texture is centered relative to background
    text_.setPosition((background.getWidth()  - text.getWidth()) >> 1, 
                      (background.getHeight() - text.getHeight()) >> 1);
}

void SButton::handleEvents(SDL_Event &event) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    // if the mouse is out of the button there're nothing to handle
    if (x < background_.getPosition().x || x > background_.getPosition().x + background_.getWidth() ||
        y < background_.getPosition().y || y > background_.getPosition().y + background_.getHeight()) {
        return;
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        std::cerr << "The button was pressed\n";
    } else {
        std::cerr << "The mouse is over the button\n";
    }
    
}

void SButton::render(SDL_Renderer* renderer) {
    background_.render(renderer);
    text_.render(renderer);
}

// assume that font texture is centered relative to background 
void SButton::setPosition(SDL_Point position) {
    int offset_x = text_.getPosition().x - background_.getPosition().x;
    int offset_y = text_.getPosition().y - background_.getPosition().y;

    text_.setPosition(position.x + offset_x, position.y + offset_y);
    background_.setPosition(position);

}
