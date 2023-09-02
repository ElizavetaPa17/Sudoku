#include "SGameLevelLabel.h"

void SGameLevelLabel::render(SDL_Renderer *renderer) {
    background_.render(renderer);
}

void SGameLevelLabel::setUp(SDL_Renderer* renderer, SConstants::GameLevel game_level) {
    switch (game_level) {
        case SConstants::GameLevel::EASY_LEVEL: {
            background_.loadFromFile(renderer, "picture/easy_level_label.png");
            break;;
        }
        case SConstants::GameLevel::MIDDLE_LEVEL: {
            background_.loadFromFile(renderer, "picture/medium_level_label.png");
            break;
        }
        case SConstants::GameLevel::HARD_LEVEL: {
            background_.loadFromFile(renderer, "picture/hard_level_label.png");
            break;
        }
        default: {
            std::cerr << "Undefined game_level in the function setLevelLabel\n";
            break;
        }
    }
}

void SGameLevelLabel::setPosition(SDL_Point position) {
    background_.setPosition(position);
}
