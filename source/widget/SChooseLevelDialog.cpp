#include "SChooseLevelDialog.h"

void SChooseLevelDialog::setUp(SDL_Renderer* renderer) {
    background_texture_.loadFromFile(renderer, "picture/choose_level_dialog.png");

    STexture button_texture;
    button_texture.loadFromFile(renderer, "picture/dialog_button.png");
    SFont font;
    font.loadFromFile("font/test_font.ttf", 30);

    font.createFontTexture(renderer, "EASY", SConstants::FONT_COLOR);

    easy_level_button_.setUp(button_texture, 
                             font.createFontTexture(renderer, "EASY", SConstants::FONT_COLOR));
    middle_level_button_.setUp(button_texture, 
                               font.createFontTexture(renderer, "MIDDLE", SConstants::FONT_COLOR));
    hard_level_button_.setUp(button_texture, 
                             font.createFontTexture(renderer, "HARD", SConstants::FONT_COLOR));

    setPosition({ 0, 0 });
}

void SChooseLevelDialog::render(SDL_Renderer *renderer) {
    background_texture_.render(renderer);
    easy_level_button_.render(renderer);
    middle_level_button_.render(renderer);
    hard_level_button_.render(renderer);
}

void SChooseLevelDialog::setPosition(SDL_Point position) {
    background_texture_.setPosition(position);
    easy_level_button_.setPosition({ position.x + 22, position.y + 130 });
    middle_level_button_.setPosition({ position.x + 162, position.y + 130 });
    hard_level_button_.setPosition({ position.x + 302, position.y + 130 });
}
