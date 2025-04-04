#include "Board.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>

#include "../Constants/BoardConstants.h"

Board::Board(std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> inputBoard, std::array<int, BOARD_COLS> inputColumnLevel)
    : board(inputBoard), columnLevel(inputColumnLevel){}

std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> Board::getBoard() const {
    return board;
}

[[nodiscard]] int Board::getColumnLevel(int col) const {
    return columnLevel[col];
}

void Board::setColumnLevel(const int col) {
    if (columnLevel[col] > 0) columnLevel[col]--;
}

int Board::makeMove(const int col, const char mark) {
    const int row = getColumnLevel(col);
    setColumnLevel(col);
    board[row][col] = mark;
    return row;
}

bool Board::validate_win(const int row, const int col, const char mark) const {
    for (const auto& dir : directions) {
        int count = 1;

        for (int i = 1; i <= WIN_COUNT; ++i) {
            int r = row + dir.first * i;
            int c = col + dir.second * i;

            if (r >= 0 && r < BOARD_ROWS && c >= 0 && c < BOARD_COLS) {
                if (board[r][c] == mark)
                    count++;
                else break;
            }
        }

        for (int i = 1; i < WIN_COUNT; ++i) {
            int r = row - dir.first * i;
            int c = col - dir.second * i;

            if (r >= 0 && r < BOARD_ROWS && c >= 0 && c < BOARD_COLS) {
                if (board[r][c] == mark)
                    count++;
                else break;
            }
        }

        if (count >= WIN_COUNT) {
            std::cout << "WINNER WINNER WINNER" << std::endl;
            return true;
        }
    }
    return false;
}

void Board::print_board() const {
    for (const auto& row : board) {
        for (const auto& col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}

