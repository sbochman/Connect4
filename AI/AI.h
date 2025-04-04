

#ifndef AI_H
#define AI_H
#include <array>

#include "../Constants/BoardConstants.h"


class AI {

    public:
        [[nodiscard]] int static makeMove(std::array<std::array<char,BOARD_COLS>, BOARD_ROWS>& board, std::array<int, BOARD_COLS>& level);

};



#endif //AI_H
