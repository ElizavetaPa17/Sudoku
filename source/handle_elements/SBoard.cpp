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
      active_cell_.first  = (y - getPosition().y) / cell_height_;
      active_cell_.second = (x - getPosition().x) / cell_width_;

       cells_[active_cell_.first][active_cell_.second].handleEvents(event); 
    }
}

void SBoard::render(SDL_Renderer *renderer) {
    cell_background_->render(renderer);

    for (int i = 0; i < CELL_DIMEN; ++i) {
        for (int j = 0; j < CELL_DIMEN; ++j) {
            cells_[i][j].render(renderer);
        }
    }
}

void SBoard::setTexture(const std::shared_ptr<STexture> texture) {
    cell_width_  = texture->getWidth() / CELL_DIMEN;
    cell_height_ = texture->getHeight() / CELL_DIMEN;

    cell_background_ = texture; 
    setPosition({ 0, 0 });
}

std::pair<int, int> SBoard::checkCells() const {
    // if active cell is space there can't be collisions
    if (cells_[active_cell_.first][active_cell_.second].getValue() == ' ') {
        return std::pair{ -1, -1 };
    }

    int active_cell_row = active_cell_.first;
    int active_cell_col = active_cell_.second;

    // row checking
    for (int col = 0; col < active_cell_col; ++col) {
        if (cells_[active_cell_row][col].getValue() == cells_[active_cell_row][active_cell_col].getValue()) 
        {
            std::cerr << "1\t";
            return active_cell_;
        }
    }
    
    for (int col = active_cell_col + 1; col < CELL_DIMEN; ++col) {
        if (cells_[active_cell_row][col].getValue() == cells_[active_cell_row][active_cell_col].getValue()) 
        {
            std::cerr << "2\t";
            return active_cell_;
        }
    }

    // column checking
    for (int row = 0; row < active_cell_row; ++row) {
        if (cells_[row][active_cell_col].getValue() == cells_[active_cell_row][active_cell_col].getValue()) 
        {
            std::cerr << "3\t";
            return active_cell_;
        }
    }
    
    for (int row = active_cell_row + 1; row < CELL_DIMEN; ++row) {
        if (cells_[row][active_cell_col].getValue() == cells_[active_cell_row][active_cell_col].getValue()) 
        {
            std::cerr << "4\t";
            return active_cell_;
        }
    }

    if (!checkRectCells(active_cell_.first, active_cell_.second)) {
        return active_cell_;
    }

    // there isn't any collision
    return std::pair{ -1, -1 };
}

// check cells in the rectangle 3*3
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
            cells_[i][j].setPosition(SDL_Point({point.x + j * cell_width_, point.y + i * cell_height_ }));
        }
    }

    cell_background_->setPosition(point);
}

/*bool SBoard::isValid() const {
    for (int i = 0; i < CELL_DIMEN; ++i) {
        for (int j = 0; j < CELL_DIMEN; ++j) {
            if (!cells_[i][j].isValid()) {
                return false;
            }
        }
    }

    return true;
}*/
