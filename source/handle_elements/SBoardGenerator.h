#pragma once

#include <vector>
#include <random>

#include "../resources/constants.h"
#include "SBoard.h"

struct InnerBoard;

class SBoardGenerator final {
public:
    static SBoardGenerator* getInstance();

    void generateNewBoard(InnerBoard& inner_board);
private:
    SBoardGenerator();
    
    void transpose(InnerBoard& inner_board);

    // swap two rows or colums within one horizontal or vertical area
    void swapSmallRows(InnerBoard& inner_board);
    void swapSmallColumns(InnerBoard& inner_board);

    // swap 3*9 horizontal or 9*3 vertical areas
    void swapRowsArea(InnerBoard& inner_board);
    void swapColumnsArea(InnerBoard& inner_board);

    void swapRows(InnerBoard& inner_board, int first_row, int second_row);
    void swapColumns(InnerBoard& inner_board, int first_column, int second_column);
    
    constexpr static int base_board_[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        4, 5, 6, 7, 8, 9, 1, 2, 3,
        7, 8, 9, 1, 2, 3, 4, 5, 6,
        2, 3, 4, 5, 6, 7, 8, 9, 1, 
        5, 6, 7, 8, 9, 1, 2, 3, 4,
        8, 9, 1, 2, 3, 4, 5, 6, 7, 
        3, 4, 5, 6, 7, 8, 9, 1, 2, 
        6, 7, 8, 9, 1, 2, 3, 4, 5,
        9, 1, 2, 3, 4, 5, 6, 7, 8
    };

    static SBoardGenerator* instance_;
    std::random_device rand_dev_;
    std::mt19937 generator_;
    std::uniform_int_distribution<> count_distrib_;
    std::uniform_int_distribution<> dimen_distrib_;
};
