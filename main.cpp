#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <SFML/Graphics.hpp>

#include "AI/AI.h"
#include "GameBoard/Board.h"

using namespace std;

constexpr int CELL_SIZE = 100;
constexpr int CIRCLE_RADIUS = 40;

int main() {
    // Create an SFML window

    sf::RenderWindow window(sf::VideoMode(BOARD_COLS * CELL_SIZE, BOARD_ROWS * CELL_SIZE), "Connect 4");
    sf::RenderWindow banner(sf::VideoMode(800, 200), "Win Banner");

    sf::Font font;
    sf::Text bannerText;
    bannerText.setFont(font);
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "Error loading font! Ensure the file path is correct." << std::endl;
        return -1;
    }
    bannerText.setString("You Win!");
    bannerText.setCharacterSize(80);
    bannerText.setFillColor(sf::Color::Green);
    sf::FloatRect textBounds = bannerText.getLocalBounds();
    bannerText.setOrigin(textBounds.left + textBounds.width / 2,
                         textBounds.top + textBounds.height / 2);
    bannerText.setPosition(banner.getSize().x / 2, banner.getSize().y / 2);


    // Grid to store circles
    std::vector<std::vector<sf::CircleShape>> board(BOARD_ROWS, std::vector<sf::CircleShape>(BOARD_COLS));
    std::array<std::array<char, BOARD_COLS>, BOARD_ROWS> boardState;
    bool player = true;

    //init board
    for (auto& row : boardState) {
        row.fill('.');
    }

    // Initialize circles
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            board[row][col].setRadius(CIRCLE_RADIUS);
            board[row][col].setFillColor(sf::Color::White); // Default empty
            board[row][col].setPosition(col * CELL_SIZE + (CELL_SIZE / 2 - CIRCLE_RADIUS),
                                        row * CELL_SIZE + (CELL_SIZE / 2 - CIRCLE_RADIUS));
        }
    }

    // Player turn tracking
    int currentPlayer = 0; // 0 = Red, 1 = Blue
    std::array<int, BOARD_COLS> columnLevel; // Tracks available row in each column

    for (auto& c : columnLevel) {
        c = BOARD_ROWS-1;
    }

    //create Board class
    Board gameBoard(boardState, columnLevel);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (currentPlayer) {
                int col = AI::makeMove(boardState, columnLevel);

                char mark = (player ? 'X' : 'O');
                int row = gameBoard.makeMove(col, mark);

                //fill board color based on col and row
                board[row][col].setFillColor(currentPlayer == 0 ? sf::Color::Red : sf::Color::Blue);

                // Switch player turn
                currentPlayer = 1 - currentPlayer;
                boardState[row][col] = (player ? 'X'  : 'O');

                player = !player;
                gameBoard.print_board();
                bool win = gameBoard.validate_win(row, col, mark);
                if (win) {
                    //add to UI "Player X WINS"
                    cout << "Player " + to_string(currentPlayer) + " won!" << endl;
                    bannerText.setString("Player " + to_string(currentPlayer) + " won!");
                    banner.clear(sf::Color::Black);
                    banner.draw(bannerText);
                    banner.display();
                }
            }

            // Handle mouse clicks
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int col = event.mouseButton.x / CELL_SIZE;

                // Place token in the lowest available row
                if (col >= 0 && col < BOARD_COLS && columnLevel[col] >= 0) {
                    char mark = (player ? 'X' : 'O');
                    int row = gameBoard.makeMove(col, mark);

                    //fill board color based on col and row
                    board[row][col].setFillColor(currentPlayer == 0 ? sf::Color::Red : sf::Color::Blue);

                    // Switch player turn
                    currentPlayer = 1 - currentPlayer;
                    boardState[row][col] = (player ? 'X'  : 'O');

                    player = !player;
                    gameBoard.print_board();
                    bool win = gameBoard.validate_win(row, col, mark);
                    if (win) {
                        //add to UI "Player X WINS"
                        cout << "Player " + to_string(currentPlayer) + " won!" << endl;
                        bannerText.setString("Player " + to_string(currentPlayer) + " won!");
                        banner.clear(sf::Color::Black);
                        banner.draw(bannerText);
                        banner.display();
                    }
                }
            }
        }

        // Render board
        window.clear(sf::Color::Black);
        for (const auto& row : board) {
            for (const auto& circle : row) {
                window.draw(circle);
            }
        }
        window.display();
    }
    cout << " Bye !" << endl;

    return 0;
}