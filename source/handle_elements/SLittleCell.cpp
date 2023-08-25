#include "SLittleCell.h"

SLittleCell::SLittleCell() 
    : background_(), value_ptr_(), value_(0), is_active_(false)
{
    setValue(' ');
}

SLittleCell::SLittleCell(const STexture& background, char value)
    : background_(background), value_ptr_(), value_(value), is_active_(false)
{
    setValue(value);
}

// assume that cell is active
void SLittleCell::handleEvents(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
    std::cerr << background_.getPosition().x / 102 << '\t' << background_.getPosition().y / 104 << '\n';
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            value_ = ' ';
        } else {
            switch (event.key.keysym.sym) {
                case SDLK_1: { setValue('1'); break; }
                case SDLK_2: { setValue('2'); break; }
                case SDLK_3: { setValue('3'); break; }
                case SDLK_4: { setValue('4'); break; }
                case SDLK_5: { setValue('5'); break; }
                case SDLK_6: { setValue('6'); break; }
                case SDLK_7: { setValue('7'); break; }
                case SDLK_8: { setValue('8'); break; }
                case SDLK_9: { setValue('9'); break; }
            }
        }
    }
}

void SLittleCell::render(SDL_Renderer *renderer) {
    background_.render(renderer);

    value_ptr_->setPosition(background_.getPosition());
    value_ptr_->render(renderer);
}

void SLittleCell::setTexture(const STexture& texture) {
    background_ = texture;
}

void SLittleCell::setValue(char value) noexcept {
    // assume that SCellFlyweight has already initialized
    value_ptr_ = SCellFlyweight::getFlyweightValue(value);
    value_ = value;
}

bool SLittleCell::isValid() const {
    return background_.isValid();
}
