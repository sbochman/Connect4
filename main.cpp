#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <SFML/Graphics.hpp>

using namespace std;

void print_board(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

bool validate_win(const vector<vector<char>>& board, const int row, const int col, const char mark) {
    const int ROWS = board.size();
    const int COLS = board[0].size();
    constexpr int WIN_COUNT = 4;

    const vector<pair<int, int>> directions = {{0, 1},{1, 0}, {1, 1}, {1, -1}};

    for (const auto& dir : directions) {
        int count = 1;
        for (int i = 1; i <= WIN_COUNT; i++) {
            const int r = row + dir.first * i;
            const int c = col + dir.second * i;

            if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                if (board[r][c] == mark)
                    count++;
                else {
                    break;
                }
            }
        }

        for (int i = 1; i < WIN_COUNT; i++) {
            const int r = row - dir.first * i;
            const int c = col - dir.second * i;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                if (board[r][c] == mark)
                    count++;
                else {
                    break;
                }
            }
        }
        if (count >= WIN_COUNT) {
            cout <<"WINNNER WINNER WINENER@" << endl;
            return true;
        }
    }
    return false;
}

bool perform_move(const bool player, vector<vector<char>>& board, unordered_map<int, int>& level) {
    const string text = to_string(player+1);
    cout <<"Enter a move Player " + text + "!" << endl;
    int move;
    cin >> move;
    cout << "Moving to " + to_string(move) << endl;
    const char mark =  player ? 'X' : 'O';
    board[level[move]][move] = mark;
    if (level[move] > 0) level[move]--;
    else perform_move(player, board, level);
    bool win = validate_win(board,level[move]+1, move, mark);
    if (win == true)
        cout << "Player " + text  + " won!" << endl;
    return win;
}

constexpr int ROWS = 6;
constexpr int COLS = 7;
constexpr int CELL_SIZE = 100;
constexpr int CIRCLE_RADIUS = 40;

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(COLS * CELL_SIZE, ROWS * CELL_SIZE), "Connect 4");
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
    std::vector<std::vector<sf::CircleShape>> board(ROWS, std::vector<sf::CircleShape>(COLS));
    std::vector<std::vector<char>> boardState(ROWS, std::vector<char>(COLS, '.'));
    bool player = true;

    // Initialize circles
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col].setRadius(CIRCLE_RADIUS);
            board[row][col].setFillColor(sf::Color::White); // Default empty
            board[row][col].setPosition(col * CELL_SIZE + (CELL_SIZE / 2 - CIRCLE_RADIUS),
                                        row * CELL_SIZE + (CELL_SIZE / 2 - CIRCLE_RADIUS));
        }
    }

    // Player turn tracking
    int currentPlayer = 0; // 0 = Red, 1 = Blue
    std::vector<int> columnLevel(COLS, ROWS - 1); // Tracks available row in each column

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle mouse clicks
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int col = event.mouseButton.x / CELL_SIZE;

                // Place token in the lowest available row
                if (col >= 0 && col < COLS && columnLevel[col] >= 0) {
                    int row = columnLevel[col];

                    // Change circle color based on player turn
                    board[row][col].setFillColor(currentPlayer == 0 ? sf::Color::Red : sf::Color::Blue);

                    // Move to the next available row in the column
                    columnLevel[col]--;

                    // Switch player turn
                    currentPlayer = 1 - currentPlayer;
                    boardState[row][col] = (player ? 'X'  : 'O');
                    char mark = (player ? 'X' : 'O');
                    player = !player;
                    print_board(boardState);
                    bool win = validate_win(boardState, row, col, mark);
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