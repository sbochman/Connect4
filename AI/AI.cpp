#include "AI.h"
#include <array>
#include <map>
#include <iostream>
#include <ostream>
#include <random>
#include "../GameBoard/Board.h"
#include "../GameBoard/BoardFactory.h"

static std::mt19937 gen(std::random_device{}());
static BoardFactory boardFactory;
int bestScore;

int AI::makeMove(const std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> &board, const std::array<int, BOARD_COLS> &level) {

    const Board currentBoard = boardFactory.createBoard(board, level);
    //std::uniform_int_distribution<> dist(0, BOARD_COLS - 1);
    //const int randomCol = dist(gen);
    //return randomCol;

    int bestMove = 0;
    bestScore = -10000;
    std::cout << "" << std::endl;
    for (int i = 0; i < BOARD_COLS; i++) {
        if (currentBoard.isValidMove(i)) {
            Board newBoard = currentBoard;
            newBoard.makeMove(i, 'X');
            std::cout<< "traversing tree" << std::endl;
            const int &score = traverseTree(newBoard, 0, false, -10000, 10000);
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }

            std::cout << "Score: " << score << std::endl;
            std::cout << "bestMove: " << bestMove << std::endl;
            std::cout << "==========================" << std::endl;
        }
        else {
            //std::cout << "No move found" << std::endl;
            if (i == bestMove) bestMove++;
        }
    }
    return bestMove;
}

std::map<std::pair<std::array<std::array<char, BOARD_COLS>, BOARD_ROWS>, bool>, int> memo;

//player - True ==> AI
//player - False ==> Player
int AI::traverseTree(Board board, const int depth, const bool player, int alpha, int beta) {
    auto key = std::make_pair(board.getBoard(), player);
    if (depth == MAX_DEPTH) {
        //std::cout << board.isGameWon(!player) << std::endl;
        const bool lastPlayerAi = !player;
        int res = board.evaluatePosition(lastPlayerAi); //not player is the previous move player. when depth is even its AI turn
        //board.print_board();
        //std::cout << res << std::endl;
        memo[key] = res;
        return res;
    }
    if (board.isGameWon(!player)) {
        const bool lastPlayerAi = !player;
        int res = board.evaluatePosition(lastPlayerAi);
        memo[key] = res;
        return res;
    }
    if (memo.contains(key)) {
        return memo[key];
    }

    int bestLocalScore = player ? -10000 : 10000;
    //else we need to recursively try all moves
    int colsPassed = 0;
    for (int col = 0; col < BOARD_COLS; col++) {
        if (board.isValidMove(col)) {
            const char mark = player ? 'X' : 'O';
            board.makeMove(col, mark);
            //board.print_board();
            //int currDepthScore = board.evaluatePosition(player, depth % 2 != 0);

            int score = traverseTree(board, depth+1, !player, alpha, beta);
            //std::cout << "score: " << score << std::endl;
            if (player) {
                bestLocalScore = std::max(bestLocalScore, score);
                alpha = std::max(alpha, bestLocalScore);
                if (beta <= alpha) break;
            }
            else {
                bestLocalScore = std::min(bestLocalScore, score);
                beta = std::min(beta, bestLocalScore);
                if (beta <= alpha) break;
            }
            //remove last move
            board.removeLastMove();
        }
        else colsPassed++;
    }
    if (colsPassed == BOARD_COLS) bestLocalScore = 0;
    //::cout << bestLocalScore << std::endl;
    memo[key] = bestLocalScore;
    return bestLocalScore;
}
