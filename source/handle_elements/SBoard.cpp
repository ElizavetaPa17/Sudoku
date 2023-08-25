#include "SBoard.h"

void SBoard::handleEvents(SDL_Event &event) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (x > getPosition().x & y > getPosition().y &&  // assume that all the cells are the same size
        x < getPosition().x + CELL_DIMEN * cell_width_ &&
        y < getPosition().y + CELL_DIMEN * cell_height_) 
    { // calculate destination
      // row corresponds to Y axis
      // column corresponds to X axis
       cells_[(y - getPosition().y) / cell_height_][(x - getPosition().x) / cell_width_].handleEvents(event); 
    }
}

void SBoard::render(SDL_Renderer *renderer) {
    for (int i = 0; i < CELL_DIMEN; ++i) {
        for (int j = 0; j < CELL_DIMEN; ++j) {
            cells_[i][j].render(renderer);
        }
    }
}

void SBoard::setTexture(const STexture& texture) {
    cell_width_  = texture.getWidth();
    cell_height_ = texture.getHeight();

    for (int i = 0; i < CELL_DIMEN; ++i) {
        for (int j = 0; j < CELL_DIMEN; ++j) {
            cells_[i][j].setTexture(texture);
        }
    }

    setPosition({0, 0});
}

// переделай проверку на наличие посредством буфера значений (входит. не входит)
bool SBoard::checkCells() const {
    for (int i = 0; i < CELL_DIMEN; ++i) {
        for (int j = 0; j < CELL_DIMEN - 1; ++j) {
            for (int k = j + 1; k < CELL_DIMEN; ++k) {
                // if values equals and aren't empty return false;
                if (cells_[i][j].getValue() == cells_[i][k].getValue() && cells_[i][j].getValue() != ' ') {
                    return false;
                }
            }
            
        }
    }

    for (int j = 0; j < CELL_DIMEN; ++j) {
        for (int i = 0; i < CELL_DIMEN - 1; ++i) {
            for (int k = i + 1; k < CELL_DIMEN; ++k) {
                if (cells_[i][j].getValue() == cells_[k][j].getValue() && cells_[i][j].getValue() != ' ') {
                    return false;
                }
            }
            
        }
    }

    int count[9] = {};
    for (int i = 0; i < CELL_DIMEN / 3; ++i) {
        for (int j = 0; j < CELL_DIMEN / 3; ++j) {
            if (!checkRectCells(i, j)) {
                return false;
            }
        }
    }

    return true;
}

bool SBoard::checkRectCells(int row_offset, int col_offset) const {
    int array[CELL_DIMEN] = {};
    for (int i = row_offset; i < row_offset + CELL_DIMEN / 3; ++i) {
        for (int j = col_offset; j < col_offset + CELL_DIMEN / 3; ++j) {
            if (cells_[i][j].getValue() != ' ') {
                ++array[cells_[i][j].getValue() - 48]; // ASCII digit numbers start from 48
            }
        }
    }

    for (int i = 0; i < CELL_DIMEN; ++i) {
        if (array[i] > 1) {
            return false;
        }
    }

    return true;
}

void SBoard::setPosition(SDL_Point point) {
    // all the cells have the same size
    for (int i = 0; i < CELL_DIMEN; ++i) {
        for (int j = 0; j < CELL_DIMEN; ++j) {
            cells_[i][j].setPosition(SDL_Point({ j * cell_width_, i * cell_height_ }));
        }
    }
}

bool SBoard::isValid() const {
    for (int i = 0; i < CELL_DIMEN; ++i) {
        for (int j = 0; j < CELL_DIMEN; ++j) {
            if (!cells_[i][j].isValid()) {
                return false;
            }
        }
    }

    return true;
}
