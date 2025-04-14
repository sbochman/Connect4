#include "Board.h"
#include <iostream>

#include "../Constants/BoardConstants.h"

Board::Board(std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> inputBoard, std::array<int, BOARD_COLS> inputColumnLevel)
    : board(inputBoard), columnLevel(inputColumnLevel){}

std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> Board::getBoard() const {
    return board;
}

[[nodiscard]] int Board::getColumnLevel(int col) const {
    return columnLevel[col];
}

void Board::printColumnLevel()const {
    for (int i = 0; i < BOARD_COLS; i++) {
        std::cout << columnLevel[i] << " ";
    }
    std::cout << std::endl;
}

[[nodiscard]] const std::array<int, BOARD_COLS>& Board::getColumnLevelArray() const {
    return columnLevel;
}

void Board::setColumnLevel(const int col) {
    if (columnLevel[col] >= 0) columnLevel[col]--;
}

int Board::makeMove(const int col, const char mark) {
    const int row = getColumnLevel(col);
    setColumnLevel(col);
    board[row][col] = mark;
    lastMove = {row, col};
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
            //std::cout << "WINNER WINNER WINNER" << std::endl;
            return true;
        }
    }
    return false;
}

bool Board::isValidMove(const int col) const {
    return getColumnLevel(col) >= 0;
}

bool Board::isGameWon(const bool player) const {
    auto [ row, col ] = lastMove;
    const char mark = player ? 'X' : 'O';
    return validate_win(row, col, mark);
}

int Board::connections(int row, int col, char mark) {
    int maxCount = 1;
    for (const auto& dir : directions) {
        int count = 0;
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
        maxCount = std::max(maxCount, count);
    }
    return maxCount;
}

bool Board::foundFork(const char mark) {
    //loop through vertical and horizont, and for each of those loop through the diagnols to check for a v shape where two missing is the diagonal
    // and one blow/above the diagonal
    int vFound = 0;
    //first check right
    for (int col = 0; col < BOARD_COLS; col++) {
        if (isValidMove(col)) {
            const int row = getColumnLevel(col) - 1;
            if (validate_win(row, col, mark)) vFound++;
        }
    }
    return vFound >= 2;
}


int Board::evaluatePosition(const bool lastPlayerWasAI) {
    auto [row, col] = lastMove;
    const char mark = lastPlayerWasAI ? 'X' : 'O';

    if (validate_win(row, col, mark)) {
        return lastPlayerWasAI ? 1000 : -1000;
    }

    if (foundFork(mark)) {
        return lastPlayerWasAI ? 900 : -900;
    }

    int score = connections(row, col, mark);

    // Bonus for playing toward center
    if (col == 3) score += 3;
    else if (col >= 2 && col <= 4) score += 1;

    return lastPlayerWasAI ? score : -score;
}


void Board::removeLastMove() {
    auto [row, col] = lastMove;
    board[row][col] = '.';
    columnLevel[col]++;
}


void Board::print_board() const {
    for (const auto& row : board) {
        for (const auto& col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}

