#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int BOARD_ROWS = 6;
constexpr int BOARD_COLS = 7;
constexpr char EMPTY_CELL = '.';
constexpr char PLAYER_ONE_MOVE = 'X';
constexpr char PLAYER_TWO_MOVE = 'O';

constexpr std::array<std::pair<int, int>, 4> directions = {{{0, 1},{1, 0}, {1, 1}, {1, -1}}};
constexpr int WIN_COUNT = 4;

#endif

