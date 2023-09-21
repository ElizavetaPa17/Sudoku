#include "SScoreLabel.h"

void SScoreLabel::render(SDL_Renderer* renderer) {
    background_texture_.render(renderer);
    score_texture_.render(renderer);
}

void SScoreLabel::setUp(SDL_Renderer* renderer, const STexture& background) {
    background_texture_ = background;
    font_.loadFromFile("font/test_font.ttf", 45);
    setScore(renderer, 0);
}

void SScoreLabel::saveChanges(SDL_Renderer* renderer) {
    score_texture_ = font_.createFontTexture(renderer, std::to_string(score_value_), SConstants::FONT_COLOR);
    score_texture_.setPosition({ background_texture_.getPosition().x + SConstants::SCORE_VALUE_OFFSET_X,
                                 background_texture_.getPosition().y + SConstants::SCORE_VALUE_OFFSET_Y});
}

// there isn't texture checking
void SScoreLabel::setScore(SDL_Renderer* renderer, int score) {
    score_value_ = score;
    saveChanges(renderer);
}

void SScoreLabel::addScore(SDL_Renderer* renderer, int score) {
    score_value_ += score;
    std::cerr << score_value_ << '\n';
    saveChanges(renderer);
}

void SScoreLabel::subScore(SDL_Renderer* renderer, int score) {
    score_value_ -= score;
    saveChanges(renderer);
}

void SScoreLabel::setPosition(SDL_Point position) {
    background_texture_.setPosition(position);
    score_texture_.setPosition({ position.x + SConstants::SCORE_VALUE_OFFSET_X, 
                                 position.y + SConstants::SCORE_VALUE_OFFSET_Y });
}
