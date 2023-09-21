#include "SBoard.h"

// create cells 9*9 dimension
SBoard::SBoard() { 
    user_cells_.resize(SConstants::CELL_DIMEN);
    inner_cells_.resize(SConstants::CELL_DIMEN);
    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        user_cells_[i].resize(SConstants::CELL_DIMEN);
        inner_cells_[i].resize(SConstants::CELL_DIMEN);
    }
}

void SBoard::handleEvents(SDL_Event &event) {
    // if the user is watching the hint we block input
    if (is_render_inner_) {
        return;
    }

    int x, y;
    SDL_GetMouseState(&x, &y);

    if (x > getPosition().x && y > getPosition().y &&
        x < getPosition().x + SConstants::CELL_DIMEN * cell_width_ &&
        y < getPosition().y + SConstants::CELL_DIMEN * cell_height_) 
    { // calculate destination
      // row corresponds to Y axis
      // column corresponds to X axi
      int current_row  = (y - getPosition().y) / cell_height_;
      int current_col  = (x - getPosition().x) / cell_width_;


      // if there any collision and user isn't fixing it we ignore any other input
      if (is_collision_ && 
         (active_cell_.first != current_row || active_cell_.second != current_col)) {
          return;
      } else {
          active_cell_ = { current_row, current_col };
          int old_value = user_cells_[current_row][current_col].getValue();

          user_cells_[current_row][current_col].handleEvents(event);
          checkCells();
        
          if (!is_collision_) {
              if (old_value == ' ' && user_cells_[current_row][current_col].getValue() != ' ') {
                  score_status_ = SConstants::ScoreStatus::ADD;
                  return;
              } else if (old_value != ' ' && user_cells_[current_row][current_col].getValue() == ' ' ) {
                  score_status_ = SConstants::ScoreStatus::SUB;
                  return;
              }
                
              score_status_ = SConstants::ScoreStatus::NO_CHANGES;
          }
      }
    }
}

void SBoard::render(SDL_Renderer *renderer) {
    cell_background_.render(renderer);

    if (is_render_inner_) {
        for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
            for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
                inner_cells_[i][j].render(renderer);
            }
        }
    } else {
        for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
            for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
                user_cells_[i][j].render(renderer);
            }
        }
    }
}

void SBoard::setTexture(const STexture& texture) {
    cell_width_  = texture.getWidth() / SConstants::CELL_DIMEN;
    cell_height_ = texture.getHeight() / SConstants::CELL_DIMEN;

    cell_background_ = texture; 
    setPosition({ 0, 0 });
}

void SBoard::checkCells() {
    // if active cell is space there can't be collisions
    if (user_cells_[active_cell_.first][active_cell_.second].getValue() == ' ') {
        is_collision_ = false; // the user resets the cell (no collision)
        return;
    }

    int active_cell_row = active_cell_.first;
    int active_cell_col = active_cell_.second;
    bool success_checking = true;

    // row checking
    for (int col = 0; col < active_cell_col; ++col) {
        if (user_cells_[active_cell_row][col].getValue() == 
            user_cells_[active_cell_row][active_cell_col].getValue()) 
        {
            success_checking = false;
        }
    }
    
    for (int col = active_cell_col + 1; col < SConstants::CELL_DIMEN; ++col) {
        if (user_cells_[active_cell_row][col].getValue() ==
            user_cells_[active_cell_row][active_cell_col].getValue()) 
        {
            success_checking = false;
        }
    }

    // column checking
    for (int row = 0; row < active_cell_row; ++row) {
        if (user_cells_[row][active_cell_col].getValue() == 
            user_cells_[active_cell_row][active_cell_col].getValue()) 
        {
            success_checking = false;
        }
    }
    
    for (int row = active_cell_row + 1; row < SConstants::CELL_DIMEN; ++row) {
        if (user_cells_[row][active_cell_col].getValue() == 
            user_cells_[active_cell_row][active_cell_col].getValue()) 
        {
            success_checking = false;
        }
    }

    // calculate 3*3 rectangle for checking
    if (success_checking && !checkRectCells((active_cell_.first / 3) * 3, (active_cell_.second / 3) * 3)) {
        success_checking = false;
    }

    // there isn't any collision
    if (success_checking) {
        is_collision_ = false;
    } else {
        is_collision_ = true;
    }
}

// check cells in the rectangle 3*3
bool SBoard::checkRectCells(int row_offset, int col_offset) const {
    int array[SConstants::CELL_DIMEN] = {};
    for (int i = row_offset; i < row_offset + SConstants::CELL_DIMEN / 3; ++i) {
        for (int j = col_offset; j < col_offset + SConstants::CELL_DIMEN / 3; ++j) {
            if (user_cells_[i][j].getValue() != ' ') {
                ++array[user_cells_[i][j].getValue() - 48]; // ASCII digit numbers start from 48
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

void SBoard::reset() {
    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
            user_cells_[i][j].setValue(' ');
        }
    }

    active_cell_ = { -1, -1 };
    is_collision_ = false;
}

void SBoard::generateNewBoard() {
    SBoardGenerator::getInstance()->generateNewBoard(inner_board);
   
    copyInnerBoard();
}

void SBoard::copyInnerBoard() {
    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
            // correct ASCII offset (numbers start from 48's position)
            inner_cells_[i][j].setValue(inner_board.board[i][j] + 48);
        }
    }
}

void SBoard::setRenderInnerBoard(bool flag) {
    is_render_inner_ = flag;
}

void SBoard::setPosition(SDL_Point point) {
    // all the cells have the same size
    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
            user_cells_[i][j].setPosition(SDL_Point({point.x + j * cell_width_,
                                                     point.y + i * cell_height_ }));
            inner_cells_[i][j].setPosition(SDL_Point({point.x + j * cell_width_,
                                                      point.y + i * cell_height_ }));
        }
    }

    cell_background_.setPosition(point);
}

SDL_Point SBoard::getPosition() {
    return cell_background_.getPosition();
}

SConstants::ScoreStatus SBoard::getScoreStatus() {
    return score_status_;
}
