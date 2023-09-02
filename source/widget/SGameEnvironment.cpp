#include "SGameEnvironment.h"

void SGameEnvironment::handleChildEvent(SWidget *child) {
    SWidget::handleChildEvent(child);
}

void SGameEnvironment::sendParentEvent() {
    SWidget::sendParentEvent();
}

void SGameEnvironment::setUp(SWidget* parent, SDL_Renderer* renderer) {
    parent_ = parent;

    STexture buffer_texture;
    buffer_texture.loadFromFile(renderer, "picture/board.png");

    board_.setTexture(buffer_texture);
    board_.setPosition({ 35, 35 });

    buffer_texture.loadFromFile(renderer, "picture/score_board.png");        
    score_label_.setUp(renderer,buffer_texture);
    score_label_.setPosition({ 460, 35 });

    buffer_texture.loadFromFile(renderer, "picture/timer_board.png");
    timer_label_.setUp(renderer, buffer_texture);
    timer_label_.setPosition({ 460, 100 });

    buffer_texture.loadFromFile(renderer, "picture/voice_control_button.png");
    voice_button_.setUp(this, buffer_texture);
    voice_button_.setPosition({ 460, 230 });

    buffer_texture.loadFromFile(renderer, "picture/show_rules_button.png");
    rules_button_.setUp(this, buffer_texture);
    rules_button_.setPosition({ 525, 230 });

    buffer_texture.loadFromFile(renderer, "picture/show_hint_button.png");
    closed_hint_button_.setUp(this, buffer_texture);
    closed_hint_button_.setPosition({ 589, 230 });

    buffer_texture.loadFromFile(renderer, "picture/hide_hint_button.png");
    opened_hint_button_.setUp(this, buffer_texture);
    opened_hint_button_.setPosition({ 589, 230 });

    buffer_texture.loadFromFile(renderer, "picture/quit_game_button.png");
    quit_game_button_.setUp(this, buffer_texture);
    quit_game_button_.setPosition({ 653, 230 });
}

void SGameEnvironment::setGameLevel(SDL_Renderer* renderer, SConstants::GameLevel game_level) {
    game_level_label_.setUp(renderer, game_level);
    game_level_label_.setPosition({ 458, 165 });
}

void SGameEnvironment::render(SDL_Renderer *renderer) {
    board_.render(renderer);
    score_label_.render(renderer);
    timer_label_.render(renderer);
    game_level_label_.render(renderer);

    voice_button_.render(renderer);
    rules_button_.render(renderer);

    if (is_opened_hint) {
        opened_hint_button_.render(renderer);
    } else {
        closed_hint_button_.render(renderer);
    }
    quit_game_button_.render(renderer);
}

void SGameEnvironment::handleEvents(SDL_Event &event) {
    board_.handleEvents(event);
    voice_button_.handleEvents(event);
    rules_button_.handleEvents(event);
    closed_hint_button_.handleEvents(event);
    opened_hint_button_.handleEvents(event);
    quit_game_button_.handleEvents(event);
}

void SGameEnvironment::startTimer() {
    timer_label_.startTimer();
}

void SGameEnvironment::stopTimer() {
    timer_label_.stopTimer();
}

void SGameEnvironment::pauseTimer() {
    timer_label_.pauseTimer();
}

void SGameEnvironment::unpauseTimer() {
    timer_label_.unpauseTimer();
}

int SGameEnvironment::getPastTicks() {
    return timer_label_.getPastTicks();
}

void SGameEnvironment::setScore(SDL_Renderer* renderer, int value) {
   score_label_.setScore(renderer, value); 
}

int SGameEnvironment::getScore() {
    return score_label_.getScore();
}
