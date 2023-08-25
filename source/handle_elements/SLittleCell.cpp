#include "SLittleCell.h"

SLittleCell::SLittleCell() 
    : value_ptr_(), position_({ 0, 0 }), value_(0)
{
    setValue(' ');
}

// assume that cell is active
void SLittleCell::handleEvents(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            setValue(' ');
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
    value_ptr_->setPosition({ position_.x + CELL_OFFSET, position_.y + CELL_OFFSET });
    value_ptr_->render(renderer);
}

void SLittleCell::setValue(char value) noexcept {
    // assume that SCellFlyweight has already initialized
    value_ptr_ = SCellFlyweight::getFlyweightValue(value);
    value_ = value;
}
