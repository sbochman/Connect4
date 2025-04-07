#pragma once
#include <array>

#include "../Constants/BoardConstants.h"

class Board {
private:
    std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> board;
    std::array<int, BOARD_COLS> columnLevel;
    std::pair<int, int> lastMove;


public:
    Board(std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> inputBoard, std::array<int, BOARD_COLS> inputColumnLevel);

    [[nodiscard]] std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> getBoard() const;

    [[nodiscard]] int getColumnLevel(int col) const;

    void printColumnLevel() const;

    [[nodisscard]] const std::array<int, BOARD_COLS>& getColumnLevelArray() const;

    void setColumnLevel(int col);

    int makeMove(int col, char mark);

    [[nodiscard]] bool validate_win(int row, int col, char mark) const;

    [[nodiscard]] bool isValidMove(int col) const;

    [[nodiscard]] int evaluatePosition(bool player);

    void removeLastMove();

    void print_board() const;

};
