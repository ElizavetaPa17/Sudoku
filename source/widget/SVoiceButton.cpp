#include "SVoiceButton.h"

void SVoiceButton::setUp(SWidget *parent, 
                         const STexture &background_texture,
                         const STexture &stop_background_texture,
                         const SChunkPlayer &chunk_player, 
                         const SMusicPlayer &music_player)
{
    SButton::setUp(parent, background_texture, chunk_player);

    stop_background_texture_ = stop_background_texture;
    music_player_ = music_player;
    music_player_.play();
}

void SVoiceButton::handleEvents(SDL_Event &event) {
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

        if (music_player_.isPlaying()) {
            music_player_.stop();
        } else {
            music_player_.play();
        }
        sendParentEvent();
    } else {
        //std::cerr << "The mouse is over the button\n";
    }
}

void SVoiceButton::render(SDL_Renderer *renderer) {
    if (music_player_.isPlaying()) {
        _background_texture.render(renderer);
    } else {
        stop_background_texture_.render(renderer);
    }
}

void SVoiceButton::setPosition(SDL_Point position) {
    _background_texture.setPosition(position);
    stop_background_texture_.setPosition(position);
}
