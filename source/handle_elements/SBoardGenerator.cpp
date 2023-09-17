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
void SBoardGenerator::generateNewBoard(std::vector<std::vector<SLittleCell>>& board) {
    int loop_count = count_distrib_(generator_);

    int new_board[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN];
    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
            new_board[i][j] = base_board[i][j];
        }
    }

    for (int i = 0; i < loop_count; ++i) {
        if (count_distrib_(generator_) % 2) { 
            transpose(new_board);
        }
        
        swapSmallRows(new_board);
        swapSmallColumns(new_board);
        swapRowsArea(new_board);
        swapColumnsArea(new_board);
    }

    // generate the first 3 rows
    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
            // ASCII correction
            board[i][j].setValue(new_board[i][j] + 48);
        }
    }
}

void SBoardGenerator::transpose(int board[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN]) {
    int temp = 0;
    for (int i = 0; i < SConstants::CELL_DIMEN; ++i) {
        for (int j = i; j < SConstants::CELL_DIMEN; ++j) {
            temp = board[i][j];
            board[i][j] = board[j][i];
            board[j][i] = temp;
        }
    }
}

void SBoardGenerator::swapSmallRows(int board[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN]) {
    int swap_count = count_distrib_(generator_);
    int area = 0, first_line = 0, second_line = 0;
    int temp = 0;

    for (int i = 0; i < swap_count; ++i) {
        area = dimen_distrib_(generator_) % 3;
        first_line = dimen_distrib_(generator_) % 3;
        second_line = dimen_distrib_(generator_) % 3;

        swapRows(board, area * 3 + first_line, area * 3 + second_line);
    }
}

void SBoardGenerator::swapSmallColumns(int board[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN]) {
    int swap_count = count_distrib_(generator_);
    int area = 0, first_line = 0, second_line = 0;
    int temp = 0;

    for (int i = 0; i < swap_count; ++i) {
        area = dimen_distrib_(generator_) % 3;
        first_line = dimen_distrib_(generator_) % 3;
        second_line = dimen_distrib_(generator_) % 3;

        swapColumns(board, area * 3 + first_line, area * 3 + second_line);
    }
}

void SBoardGenerator::swapRowsArea(int board[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN]) {
    int swap_count = count_distrib_(generator_);
    int first_row_area = 0, second_row_area = 0;
    int temp = 0;

    for (int i = 0; i < swap_count; ++i) {
        first_row_area = dimen_distrib_(generator_) % 3;
        second_row_area = dimen_distrib_(generator_) % 3;
        
        for (int j = 0; j < 3; ++j) {
            swapRows(board, first_row_area * 3 + j, second_row_area * 3 + j);
        }
    }
}

void SBoardGenerator::swapColumnsArea(int board[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN]) {
    int swap_count = count_distrib_(generator_);
    int first_column_area = 0, second_column_area = 0;
    int temp = 0;

    for (int i = 0; i < swap_count; ++i) {
        first_column_area = dimen_distrib_(generator_) % 3;
        second_column_area = dimen_distrib_(generator_) % 3;
        
        for (int j = 0; j < 3; ++j) {
            swapColumns(board, first_column_area * 3 + j, second_column_area * 3 + j);
        }
    }
}

void SBoardGenerator::swapRows(int board[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN],
                               int first_row, int second_row) {
    int temp = 0;
    for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
        std::swap(board[first_row][j], board[second_row][j]);
    }    
}

void SBoardGenerator::swapColumns(int board[SConstants::CELL_DIMEN][SConstants::CELL_DIMEN], 
                                  int first_column, 
                                  int second_column)
{
    int temp = 0;
    for (int j = 0; j < SConstants::CELL_DIMEN; ++j) {
        temp = board[j][first_column];
        board[j][first_column] = board[j][second_column];
        board[j][second_column] = temp;
    }
    
}
