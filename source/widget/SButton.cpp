#include "SButton.h"

SButton::SButton(const STexture& background, const STexture& text) 
    : background_texture(background), text_texture(text)
{   
    // assume that font texture is centered relative to background
    text_texture.setPosition((background.getWidth()  - text.getWidth()) >> 1, 
                      (background.getHeight() - text.getHeight()) >> 1);
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
    text_texture.render(renderer);
}

void SButton::setUp(SWidget* parent, const STexture &background, const STexture &text) {
    parent_ = parent;
    background_texture = background;
    text_texture = text;

    setPosition(background.getPosition());
}

// assume that font texture is centered relative to background 
void SButton::setPosition(SDL_Point position) {
    background_texture.setPosition(position);
    
    int text_pos_x = ((background_texture.getWidth() - text_texture.getWidth()) >> 1) + 
                       background_texture.getPosition().x;
    int text_pos_y = ((background_texture.getHeight() - text_texture.getHeight()) >> 1) +
                       background_texture.getPosition().y;;
    text_texture.setPosition({ text_pos_x, text_pos_y });
}
