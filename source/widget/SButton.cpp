#include "SButton.h"

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
    if (x < _background_texture.getPosition().x || 
        x > _background_texture.getPosition().x + _background_texture.getWidth() ||
        y < _background_texture.getPosition().y || 
        y > _background_texture.getPosition().y + _background_texture.getHeight()) {
        return;
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        chunk_player_.play();
        sendParentEvent();
    } else {
        //std::cerr << "The mouse is over the button\n";
    }
    
}

void SButton::render(SDL_Renderer* renderer) {
    _background_texture.render(renderer);
}

void SButton::setUp(SWidget* parent, const STexture &background_texture, const SChunkPlayer& chunk_player) {
    parent_ = parent;
    _background_texture = background_texture;
    chunk_player_ = chunk_player;

    setPosition(_background_texture.getPosition());
}

// assume that font texture is centered relative to background 
void SButton::setPosition(SDL_Point position) {
    _background_texture.setPosition(position);
}
