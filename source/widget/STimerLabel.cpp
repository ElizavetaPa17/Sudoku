#include "STimerLabel.h"

void STimerLabel::updateTimer(SDL_Renderer* renderer) {
    timer_texture_ = convertTicks(renderer);

    // update timer_texture_position
    timer_texture_.setPosition({ background_texture_.getPosition().x + SConstants::TIMER_VALUE_OFFSET_X, 
                                 background_texture_.getPosition().y + SConstants::TIMER_VALUE_OFFSET_Y });
}

STexture  STimerLabel::convertTicks(SDL_Renderer* renderer) {
    // return value in milliseconds
    int timer_ticks = timer_.getTicks();

    // convert ticks to the format "minutes:seconds"
    return font_.createFontTexture(renderer, 
                                   std::to_string((timer_ticks / 60000) % 60) + ":" +
                                   std::to_string((timer_ticks / 1000)  % 60), SConstants::FONT_COLOR);
}

void STimerLabel::setUp(SDL_Renderer* renderer, const STexture& background_texture) {
    background_texture_ = background_texture;
    font_.loadFromFile("font/test_font.ttf", 40);
    timer_texture_ = font_.createFontTexture(renderer, "00:00", SConstants::FONT_COLOR);
    setPosition(background_texture.getPosition());
}

void STimerLabel::render(SDL_Renderer *renderer) {
    background_texture_.render(renderer);

    updateTimer(renderer);
    timer_texture_.render(renderer);
}

void STimerLabel::setPosition(SDL_Point position) {
    background_texture_.setPosition(position);
    timer_texture_.setPosition({ position.x + SConstants::TIMER_VALUE_OFFSET_X, 
                                 position.y + SConstants::TIMER_VALUE_OFFSET_Y });
}

void STimerLabel::startTimer() {
    timer_.start();
}

void STimerLabel::stopTimer() {
    timer_.stop();
}

void STimerLabel::pauseTimer() {
    timer_.pause();
}

void STimerLabel::unpauseTimer() {
    timer_.unpause();
}

int STimerLabel::getPastTicks() {
    return timer_.getTicks();    
}
