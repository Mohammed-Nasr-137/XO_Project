#include "game.hpp"
#include <iostream>
using namespace std;

Game::Game()
{
    board = vector<vector<char>>(3, vector<char>(3, ' '));
    currentPlayer = 'X';
}

void Game::displayBoard() const 
{
    cout << "\n";
    for (int i = 0; i < 3; ++i)
    {
        cout << " ";
        for (int j = 0; j < 3; ++j)
        {
            cout << board[i][j];
            if (j < 2) 
                cout << " | ";
        }

        if (i < 2) cout << "\n-----------\n";
    }
    cout << "\n";
}

bool Game::makeMove(int row, int col)
{
    if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ')
        return false;

    board[row][col] = currentPlayer;
    return true;
}

void Game::switchPlayer() {    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';  }

bool Game::checkWin() const 
{
    // check rows, columns, diagonals
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer) return true;
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer) return true;
    }
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer) return true;
    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer) return true;

    return false;
}

bool Game::checkDraw() const 
{
    for (auto& row : board)
        for (char cell : row)
            if (cell == ' ') return false;
    return true;
}



void Game::play() 
{
    int row, col;
    while (true) 
    {
        displayBoard();
        std::cout << "Player " << currentPlayer << ", enter row and column (0-2): ";
        std::cin >> row >> col;

        if (!makeMove(row, col)) {
            std::cout << "Invalid move. Try again.\n";
            continue;
        }

        if (checkWin()) {
            displayBoard();
            std::cout << "Player " << currentPlayer << " wins!\n";
            break;
        }

        if (checkDraw()) {
            displayBoard();
            std::cout << "It’s a draw!\n";
            break;
        }

        switchPlayer();
    }
}
