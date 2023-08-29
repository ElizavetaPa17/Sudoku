#include "SBoard.h"

void SBoard::handleEvents(SDL_Event &event) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    // assume that all the cells are the same size
    if (x > getPosition().x && y > getPosition().y &&
        x < getPosition().x + SConstants::CELL_DIMEN * cell_width_ &&
        y < getPosition().y + SConstants::CELL_DIMEN * cell_height_) 
    { // calculate destination
      // row corresponds to Y axis
      // column corresponds to X axi
      int current_cell_row  = (y - getPosition().y) / cell_height_;
      int current_cell_col  = (x - getPosition().x) / cell_width_;

      // if there any collision and user isn't fixing it we ignore any other input
      //std::cerr << is_collision_ << '\n';
      if (is_collision_ && 
         (active_cell_.first != current_cell_row || active_cell_.second != current_cell_col)) {
          return;
      } else {
          active_cell_ = { current_cell_row, current_cell_col };
          cells_[current_cell_row][current_cell_col].handleEvents(event); 
      }
    }
}

void SBoard::render(SDL_Renderer *renderer) {
    cell_background_->render(renderer);

    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
            cells_[i][j].render(renderer);
        }
    }
}

void SBoard::setTexture(const std::shared_ptr<STexture> texture) {
    cell_width_  = texture->getWidth() / SConstants::CELL_DIMEN;
    cell_height_ = texture->getHeight() / SConstants::CELL_DIMEN;

    cell_background_ = texture; 
    setPosition({ 0, 0 });
}

std::pair<int, int> SBoard::checkCells() {
    // if active cell is space there can't be collisions
    if (cells_[active_cell_.first][active_cell_.second].getValue() == ' ') {
        is_collision_ = false; // the user resets the cell (no collision)
        return std::pair{ -1, -1 };
    }

    int active_cell_row = active_cell_.first;
    int active_cell_col = active_cell_.second;
    bool success_checking = true;

    // row checking
    for (int col = 0; col < active_cell_col; ++col) {
        if (cells_[active_cell_row][col].getValue() == cells_[active_cell_row][active_cell_col].getValue()) 
        {
            success_checking = false;
        }
    }
    
    for (int col = active_cell_col + 1; col < SConstants::CELL_DIMEN; ++col) {
        if (cells_[active_cell_row][col].getValue() == cells_[active_cell_row][active_cell_col].getValue()) 
        {
            success_checking = false;
        }
    }

    // column checking
    for (int row = 0; row < active_cell_row; ++row) {
        if (cells_[row][active_cell_col].getValue() == cells_[active_cell_row][active_cell_col].getValue()) 
        {
            success_checking = false;
        }
    }
    
    for (int row = active_cell_row + 1; row < SConstants::CELL_DIMEN; ++row) {
        if (cells_[row][active_cell_col].getValue() == cells_[active_cell_row][active_cell_col].getValue()) 
        {
            success_checking = false;
        }
    }

    if (success_checking && !checkRectCells(active_cell_.first, active_cell_.second)) {
        success_checking = false;
    }

    // there isn't any collision
    if (success_checking) {
        is_collision_ = false;
        return std::pair{ -1, -1 };
    } else {
        is_collision_ = true;
        return active_cell_;
    }
}

// check cells in the rectangle 3*3
bool SBoard::checkRectCells(int row_offset, int col_offset) const {
    int array[SConstants::CELL_DIMEN] = {};
    for (int i = row_offset; i < row_offset + SConstants::CELL_DIMEN / 3; ++i) {
        for (int j = col_offset; j < col_offset + SConstants::CELL_DIMEN / 3; ++j) {
            if (cells_[i][j].getValue() != ' ') {
                ++array[cells_[i][j].getValue() - 48]; // ASCII digit numbers start from 48
            }
        }
    }

    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        if (array[i] > 1) {
            return false;
        }
    }

    return true;
}

void SBoard::setPosition(SDL_Point point) {
    // all the cells have the same size
    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
            cells_[i][j].setPosition(SDL_Point({point.x + j * cell_width_, point.y + i * cell_height_ }));
        }
    }

    cell_background_->setPosition(point);
}
