#include "SButton.h"

SButton::SButton(const STexture& background) 
    : background_texture(background)
{   
}

//default realization
void SButton::handleChildEvent(SWidget *child) {
    SWidget::handleChildEvent(child);
}

void SButton::sendParentEvent() {
    parent_->handleChildEvent(this);
}

void SButton::handleEvents(SDL_Event &event) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    // if the mouse is out of the button there're nothing to handle
    if (x < background_texture.getPosition().x || 
        x > background_texture.getPosition().x + background_texture.getWidth() ||
        y < background_texture.getPosition().y || 
        y > background_texture.getPosition().y + background_texture.getHeight()) {
        return;
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        sendParentEvent();
    } else {
        //std::cerr << "The mouse is over the button\n";
    }
    
}

void SButton::render(SDL_Renderer* renderer) {
    background_texture.render(renderer);
}

void SButton::setUp(SWidget* parent, const STexture &background) {
    parent_ = parent;
    background_texture = background;

    setPosition(background.getPosition());
}

// assume that font texture is centered relative to background 
void SButton::setPosition(SDL_Point position) {
    background_texture.setPosition(position);
}
