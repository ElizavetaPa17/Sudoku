#include "SBoardGenerator.h"

SBoardGenerator* SBoardGenerator::instance_ = nullptr;

SBoardGenerator::SBoardGenerator() : generator_(rand_dev_()), count_distrib_(1, 20), dimen_distrib_(0, 8)
{
}

SBoardGenerator* SBoardGenerator::getInstance() {
    if (instance_ == nullptr) {
        instance_ = new SBoardGenerator();
    }

    return instance_;
}

// Base Sudoku Generator
void SBoardGenerator::generateNewBoard(InnerBoard& inner_board) {
    int loop_count = count_distrib_(generator_);

    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
            inner_board.board[i][j] = base_board_[i][j];
        }
    }

    for (int i = 0; i < loop_count; ++i) {
        if (count_distrib_(generator_) % 2) { 
            transpose(inner_board);
        }
        
        swapSmallRows(inner_board);
        swapSmallColumns(inner_board);
        swapRowsArea(inner_board);
        swapColumnsArea(inner_board);
    }
}

void SBoardGenerator::transpose(InnerBoard& inner_board) {
    int temp = 0;
    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = i; j < SConstants::CELL_DIMEN; ++j) {
            std::swap(inner_board.board[i][j], inner_board.board[j][i]);
        }
    }
}

void SBoardGenerator::swapSmallRows(InnerBoard& inner_board) {
    int swap_count = count_distrib_(generator_);
    int area = 0, first_line = 0, second_line = 0;
    int temp = 0;

    for (int i = 0; i < swap_count; ++i) {
        area = dimen_distrib_(generator_) % 3;
        first_line = dimen_distrib_(generator_) % 3;
        second_line = dimen_distrib_(generator_) % 3;

        swapRows(inner_board, area * 3 + first_line, area * 3 + second_line);
    }
}

void SBoardGenerator::swapSmallColumns(InnerBoard& inner_board) {
    int swap_count = count_distrib_(generator_);
    int area = 0, first_line = 0, second_line = 0;
    int temp = 0;

    for (int i = 0; i < swap_count; ++i) {
        area = dimen_distrib_(generator_) % 3;
        first_line = dimen_distrib_(generator_) % 3;
        second_line = dimen_distrib_(generator_) % 3;

        swapColumns(inner_board, area * 3 + first_line, area * 3 + second_line);
    }
}

void SBoardGenerator::swapRowsArea(InnerBoard& inner_board) {
    int swap_count = count_distrib_(generator_);
    int first_row_area = 0, second_row_area = 0;
    int temp = 0;

    for (int i = 0; i < swap_count; ++i) {
        first_row_area = dimen_distrib_(generator_) % 3;
        second_row_area = dimen_distrib_(generator_) % 3;
        
        for (int j = 0; j < 3; ++j) {
            swapRows(inner_board, first_row_area * 3 + j, second_row_area * 3 + j);
        }
    }
}

void SBoardGenerator::swapColumnsArea(InnerBoard& inner_board) {
    int swap_count = count_distrib_(generator_);
    int first_column_area = 0, second_column_area = 0;
    int temp = 0;

    for (int i = 0; i < swap_count; ++i) {
        first_column_area = dimen_distrib_(generator_) % 3;
        second_column_area = dimen_distrib_(generator_) % 3;
        
        for (int j = 0; j < 3; ++j) {
            swapColumns(inner_board, first_column_area * 3 + j, second_column_area * 3 + j);
        }
    }
}

void SBoardGenerator::swapRows(InnerBoard& inner_board, int first_row, int second_row) {
    int temp = 0;
    for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
        std::swap(inner_board.board[first_row][j], inner_board.board[second_row][j]);
    }    
}

void SBoardGenerator::swapColumns(InnerBoard& inner_board, int first_column, int second_column)
{
    int temp = 0;
    for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
        std::swap(inner_board.board[j][first_column], inner_board.board[j][second_column]);
    }
    
}


