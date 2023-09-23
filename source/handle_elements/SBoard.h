#pragma once

#include <SDL2/SDL.h>
#include <utility>
#include <random>
#include <vector>

#include "SLittleCell.h"
#include "SBoardGenerator.h"
#include "SSudokuSolver.h"
#include "../resources/constants.h"

struct InnerBoard final {
    int board[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN]{};
};

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
    void generateNewBoard(SConstants::GameLevel level);

    void setRenderInnerBoard(bool flag);

    void setPosition(SDL_Point point);
    SDL_Point getPosition();
    
    SConstants::ScoreStatus getScoreStatus();
    void setScoreStatus(SConstants::ScoreStatus status) { score_status_ = status; }

private:
    bool checkRectCells(int row_offset, int col_offset) const;
    void copyInnerBoard();

    std::vector<std::vector<SLittleCell>> user_cells_;
    STexture cell_background_;    

    InnerBoard inner_board;
    std::vector<std::vector<SLittleCell>> inner_cells_;
    bool render_cells_[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN]{};
    bool is_render_inner_ = false;

    int cell_width_  = 0;
    int cell_height_ = 0; 

    // the cell that handles user input at the moment
    // comprises  row and collumn
    std::pair<int, int> active_cell_ = { -1, -1 };
    bool is_collision_ = false;

    SConstants::ScoreStatus score_status_ = SConstants::ScoreStatus::NO_CHANGES;
};
