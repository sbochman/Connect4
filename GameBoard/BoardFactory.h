//
// Created by seanb on 4/4/2025.
//

#ifndef BOARDFACTORY_H
#define BOARDFACTORY_H
#include "Board.h"


class BoardFactory {

public:
    BoardFactory() = default;

    [[nodiscard]]
    static Board createBoard(const std::array<std::array<char, BOARD_COLS>, BOARD_ROWS>& board, const std::array<int, BOARD_COLS>& level);

};



#endif //BOARDFACTORY_H
