//
// Created by seanb on 4/4/2025.
//

#include "BoardFactory.h"

Board BoardFactory::createBoard(const std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> &board, const std::array<int, BOARD_COLS> &level) {
    return Board(board, level);
}
