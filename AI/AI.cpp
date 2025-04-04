//
// Created by seanb on 4/3/2025.
//

#include "AI.h"

#include <array>
#include <random>

#include "../GameBoard/Board.h"

static std::mt19937 gen(std::random_device{}());

int AI::makeMove(std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> &board, std::array<int, BOARD_COLS> &level) {

    Board currentBoard(board, level);

    std::uniform_int_distribution<> dist(0, BOARD_COLS - 1);
    const int randomCol = dist(gen);
    return randomCol;
}
