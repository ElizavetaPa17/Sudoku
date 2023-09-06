#include "SRulesButton.h"
#include <cstdlib>

void SRulesButton::setUp(SWidget *parent, 
                         const STexture &background_texture, 
                         const STexture &rules_hint_texture)
{
    SButton::setUp(parent, background_texture);

    _rules_hint_texture = rules_hint_texture;
}

void SRulesButton::handleEvents(SDL_Event &event) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    // if the mouse is out of the button there're nothing to handle
    if (x < _background_texture.getPosition().x || 
        x > _background_texture.getPosition().x + _background_texture.getWidth() ||
        y < _background_texture.getPosition().y || 
        y > _background_texture.getPosition().y + _background_texture.getHeight()) 
    {    
        _render_hint_menu = false;
        return;
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        system("nohup xdg-open \"https://sudoku.com/ru/pravila-sudoku/\"");
        sendParentEvent();
    } else {
        _render_hint_menu = true;
    }
}

void SRulesButton::render(SDL_Renderer *renderer) {
    SButton::render(renderer);
    
    if (_render_hint_menu) {
        _rules_hint_texture.render(renderer);
    }
}

void SRulesButton::setPosition(SDL_Point position) {
    SButton::setPosition(position);

    _rules_hint_texture.setPosition({ position.x + SConstants::RULES_HINT_OFFSET.x, 
                                      position.y + SConstants::RULES_HINT_OFFSET.y});
}
