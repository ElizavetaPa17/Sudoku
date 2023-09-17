#pragma once

#include <SDL2/SDL.h>
#include <utility>
#include <vector>

#include "SLittleCell.h"
#include "SBoardGenerator.h"
#include "../resources/constants.h"

class SBoard final {
public:
    // don't declare copy and move constructor and assignment (they're deleted implicitly)
    // get the renderer because is responsible for setting background
    SBoard();
    ~SBoard() = default;

    void handleEvents(SDL_Event& event);
    void render(SDL_Renderer* renderer);
    void setTexture(const STexture& texture);

    // return pair comprises the row and column of the collision
    // if there isn't any collision return pair(-1, -1)
    void checkCells();
    void reset();
    void generateNewBoard();

    void setPosition(SDL_Point point);
    SDL_Point getPosition() { return cell_background_.getPosition(); }

private:
    bool checkRectCells(int row_offset, int col_offset) const;

    std::vector<std::vector<SLittleCell>> cells_;
    STexture cell_background_;    

    int cell_width_  = 0;
    int cell_height_ = 0; 

    // the cell that handles user input at the moment
    // comprises  row and collumn
    std::pair<int, int> active_cell_ = { -1, -1 };
    bool is_collision_ = false;
};
