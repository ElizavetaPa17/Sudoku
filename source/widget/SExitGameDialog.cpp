#include "SExitGameDialog.h"

void SExitGameDialog::handleChildEvent(SWidget *child) {
    if (&agree_button_ == child) {
        game_state_ = SConstants::GameState::QUIT;
    } else {
        game_state_ = SConstants::GameState::PLAY;
    }

    sendParentEvent();
}

void SExitGameDialog::sendParentEvent() {
    parent_->handleChildEvent(this);
}

void SExitGameDialog::setUp(SWidget *parent, SDL_Renderer *renderer) {
    parent_ = parent;

    SChunkPlayer chunk_player;
    chunk_player.loadFromFile(SConstants::chunk_path);

    background_texture_.loadFromFile(renderer, "picture/quit_game_dialog.png");

    STexture buffer_texture;
    buffer_texture.loadFromFile(renderer, "picture/agree_quit_button.png");
    agree_button_.setUp(this, buffer_texture, chunk_player);

    buffer_texture.loadFromFile(renderer, "picture/disagree_quit_button.png");
    disagree_button_.setUp(this, buffer_texture, chunk_player);

    setPosition({ 0, 0 });
}

void SExitGameDialog::handleEvents(SDL_Event &event) {
    agree_button_.handleEvents(event);
    disagree_button_.handleEvents(event);
}

void SExitGameDialog::render(SDL_Renderer *renderer) {
    background_texture_.render(renderer);

    agree_button_.render(renderer);
    disagree_button_.render(renderer);
}

void SExitGameDialog::setPosition(SDL_Point position) {
    background_texture_.setPosition(position);

    agree_button_.setPosition({ position.x + 18, position.y + 90 });
    disagree_button_.setPosition({ position.x + 140, position.y + 90 });
}

SConstants::GameState SExitGameDialog::getGameState() { 
    return game_state_;
}
