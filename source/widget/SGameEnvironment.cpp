#include "SGameEnvironment.h"

void SGameEnvironment::handleChildEvent(SWidget *child) {
    SWidget::handleChildEvent(child);
}

void SGameEnvironment::sendParentEvent() {
    SWidget::sendParentEvent();
}

void SGameEnvironment::setUp(SWidget* parent, SDL_Renderer* renderer) {
    parent_ = parent;

    STexture board_texture;
    board_texture.loadFromFile(renderer, "picture/board.png");

    board_.setTexture(board_texture);
    board_.setPosition({ 35, 35 });

    STexture score_background;
    score_background.loadFromFile(renderer, "picture/score_board.png");        
    score_label_.setUp(renderer, score_background);
    score_label_.setPosition({ 458, 35 });

    STexture timer_background;
    timer_background.loadFromFile(renderer, "picture/timer_board.png");
    timer_label_.setUp(renderer, timer_background);
    timer_label_.setPosition({ 458, 100 });
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
}

void SGameEnvironment::handleEvents(SDL_Event &event) {
    board_.handleEvents(event);
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