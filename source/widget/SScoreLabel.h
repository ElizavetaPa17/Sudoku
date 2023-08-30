#pragma once

#include "../renderer/STexture.h"
#include "../renderer/SFont.h"
#include "../resources/constants.h"

class SScoreLabel final {
public:
    SScoreLabel() = default;
    
    void render(SDL_Renderer* renderer);

    // must be set up before using. set texture, load font, set initial score value (zero)
    void setUp(SDL_Renderer* renderer, const STexture& background);

    void setScore(SDL_Renderer* renderer, int score);
    int  getScore() const { return score_value_; };

    void setPosition(SDL_Point position);

    // assume that label position is background position
    SDL_Point getPosition() const;

private:
    STexture background_texture_;
    STexture score_texture_;
    SFont font_;

    int score_value_ = 0;
};
