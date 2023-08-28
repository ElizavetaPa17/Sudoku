#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <utility>

#include "SLittleCell.h"

const int CELL_DIMEN = 9;
const int CELL_COUNT = CELL_DIMEN * CELL_DIMEN;

class SBoard final {
public:
    // don't declare copy and move constructor and assignment (they're deleted implicitly)
    // get the renderer because is responsible for setting background
    SBoard() = default;
    ~SBoard() = default;

    void handleEvents(SDL_Event& event);
    void render(SDL_Renderer* renderer);
    void setTexture(const std::shared_ptr<STexture> texture);

    // return pair comprises the row and column of the collision
    // if there isn't any collision return pair(-1, -1)
    std::pair<int, int> checkCells();

    void setPosition(SDL_Point point);
    SDL_Point getPosition() const noexcept { return cells_[0][0].getPosition(); }

//    bool isValid() const; // return true if all the cells are valid (has background texture)

private:
    bool checkRectCells(int row_offset, int col_offset) const;

    SLittleCell cells_[CELL_DIMEN][CELL_DIMEN];
    std::shared_ptr<STexture> cell_background_;    

    int cell_width_  = 0;
    int cell_height_ = 0; 

    // the cell that handles user input at the moment
    // comprises  row and collumn
    std::pair<int, int> active_cell_;
    bool is_collision_ = false;
};
