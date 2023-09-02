#include "SChooseLevelDialog.h"

void SChooseLevelDialog::handleChildEvent(SWidget *child) {
    if (&easy_level_button_ == child) {
        game_level_ = SConstants::GameLevel::EASY_LEVEL;
    } else if (&medium_level_button_ == child) {
        game_level_ = SConstants::GameLevel::MIDDLE_LEVEL;
    } else if (&hard_level_button_ == child) {
        game_level_ = SConstants::GameLevel::HARD_LEVEL;
    }

    sendParentEvent();
}

void SChooseLevelDialog::sendParentEvent() {
    parent_->handleChildEvent(this);
}

void SChooseLevelDialog::setUp(SWidget* parent, SDL_Renderer* renderer) {
    parent_ = parent;

    background_texture_.loadFromFile(renderer, "picture/choose_level_dialog.png");

    STexture button_texture;
    button_texture.loadFromFile(renderer, "picture/easy_level_button.png");
    easy_level_button_.setUp(this, button_texture);

    button_texture.loadFromFile(renderer, "picture/medium_level_button.png");
    medium_level_button_.setUp(this, button_texture);

    button_texture.loadFromFile(renderer, "picture/hard_level_button.png");
    hard_level_button_.setUp(this, button_texture);

    setPosition({ 0, 0 });
}

void SChooseLevelDialog::render(SDL_Renderer *renderer) {
    background_texture_.render(renderer);
    easy_level_button_.render(renderer);
    medium_level_button_.render(renderer);
    hard_level_button_.render(renderer);
}

void SChooseLevelDialog::handleEvents(SDL_Event &event) {
    easy_level_button_.handleEvents(event);
    medium_level_button_.handleEvents(event);
    hard_level_button_.handleEvents(event);
}

void SChooseLevelDialog::setPosition(SDL_Point position) {
    background_texture_.setPosition(position);
    easy_level_button_.setPosition({ position.x + 22, position.y + 130 });
    medium_level_button_.setPosition({ position.x + 162, position.y + 130 });
    hard_level_button_.setPosition({ position.x + 302, position.y + 130 });
}

typename SConstants::GameLevel SChooseLevelDialog::getGameLevel() {
    return game_level_;
}
