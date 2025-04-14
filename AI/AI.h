#ifndef AI_H
#define AI_H
#include <array>

#include "../Constants/BoardConstants.h"
#include "../GameBoard/Board.h"


class AI {
private:
    [[nodiscard]] int traverseTree(Board board, int depth, bool player, int alpha, int beta);

public:
    [[nodiscard]] int makeMove(const std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> &board,
                                      const std::array<int, BOARD_COLS> &level);
};


#endif //AI_H
