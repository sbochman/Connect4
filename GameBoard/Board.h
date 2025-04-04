#pragma once
#include <array>

#include "../Constants/BoardConstants.h"

class Board {
    private:
        std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> board;
        std::array<int, BOARD_COLS> columnLevel;

    public:
        Board(std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> inputBoard, std::array<int, BOARD_COLS> inputColumnLevel);

        [[nodiscard]] std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> getBoard() const;

        [[nodiscard]] int getColumnLevel(int col) const;

        void setColumnLevel(int col);

        [[nodiscard]] int makeMove(int col, const char mark);

        [[nodiscard]] bool validate_win(int row, int col, char mark) const;

        void print_board() const;

};
