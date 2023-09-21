#pragma once

#include "../renderer/STexture.h"
#include "../renderer/SFont.h"
#include "../resources/constants.h"

class SScoreLabel final {
public:
    SScoreLabel() = default;
    
    // must be set up before using. set texture, load font, set initial score value (zero)
    void setUp(SDL_Renderer* renderer, const STexture& background);
    void render(SDL_Renderer* renderer);


    void setScore(SDL_Renderer* renderer, int score);
    void addScore(SDL_Renderer* renderer, int score);
    void subScore(SDL_Renderer* renderer, int score);
    int  getScore() const { return score_value_; };

    void setPosition(SDL_Point position);

private:
    void saveChanges(SDL_Renderer* renderer);

    STexture background_texture_;
    STexture score_texture_;
    SFont font_;

    int score_value_ = 0;
};
