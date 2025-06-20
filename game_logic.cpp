#include "game_logic.h"
#include <iostream>

using namespace std;
// --- Private Methods ---

int GameEngine::playerValue(char cell) {
    if (cell == 'X') return 1;
    if (cell == 'O') return -1;
    return 0;
}

// --- Public Methods ---

void GameEngine::Game_init() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
    currentPlayer = 'X';
    moveHistory.clear();
}

Board GameEngine::get_board() const {
    return board;
}

const std::vector<std::pair<Move, std::string>>& GameEngine::get_moveHistory() const {
    return moveHistory;
}

char GameEngine::getCurrentPlayer() const {
    return currentPlayer;
}

char GameEngine::getOpponentPlayer() const {
    return (currentPlayer == 'X') ? 'O' : 'X';
}

bool GameEngine::isValidMove(int position) {
    if (position < 1 || position > 9) {
        return false;
    }
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    return board[row][col] == ' ';
}

bool GameEngine::makeMove(int position, const std::string& comment) {
    if (isValidMove(position)) {
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;
        board[row][col] = currentPlayer;
        moveHistory.push_back({{position, currentPlayer}, comment});
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        return true;
    }
    return false;
}

bool GameEngine::undoMove() {
    if (moveHistory.empty()) {
        return false;
    }
    std::pair<Move, std::string> lastMove = moveHistory.back();
    moveHistory.pop_back();
    int row = (lastMove.first.position - 1) / 3;
    int col = (lastMove.first.position - 1) % 3;
    board[row][col] = ' ';
    currentPlayer = lastMove.first.player;
    return true;
}


pair<bool, int> GameEngine::checkWin(string player)
{
    // Check for X (sum = 3) and O (sum = -3)
    for (const auto& [player, targetSum] : {std::pair{'X', 3}, {'O', -3}})
    {
        // Check win lines 1,2,3
        for (int row = 0; row < 3; ++row)
        {
            int sum = playerValue(board[row][0]) + playerValue(board[row][1]) + playerValue(board[row][2]);
            if (sum == targetSum)
            {
                return {true, row + 1};
            }
        }

        // Check win lines 4,5,6
        for (int col = 0; col < 3; ++col)
        {
            int sum = playerValue(board[0][col]) + playerValue(board[1][col]) + playerValue(board[2][col]);
            if (sum == targetSum)
            {
                return {true, col + 4};
            }
        }

        // Check win line 7
        int diag1 = playerValue(board[0][0]) + playerValue(board[1][1]) + playerValue(board[2][2]);
        if (diag1 == targetSum)
        {
            return {true, 7};
        }

        // Check win line 8
        int diag2 = playerValue(board[0][2]) + playerValue(board[1][1]) + playerValue(board[2][0]);
        if (diag2 == targetSum)
        {
            return {true, 8};
        }
    }
    return {false, -1};
}


/*
bool GameEngine::checkWin(std::string player) {
    int val = (player == "X") ? 1 : -1;
    // std::cout << player << " " << val << "\n";
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((playerValue(board[i][0]) + playerValue(board[i][1]) + playerValue(board[i][2]) == 3 * val) ||
            (playerValue(board[0][i]) + playerValue(board[1][i]) + playerValue(board[2][i]) == 3 * val)) {
            return true;
        }
    }
    // Check diagonals
    if ((playerValue(board[0][0]) + playerValue(board[1][1]) + playerValue(board[2][2]) == 3 * val) ||
        (playerValue(board[0][2]) + playerValue(board[1][1]) + playerValue(board[2][0]) == 3 * val)) {
        return true;
    }
    return false;
}*/

bool GameEngine::checkDraw() {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;
            }
        }
    }
    // A draw is only true if the board is full AND no one has won
    return !checkWin("X").first && !checkWin("O").first;
}

bool GameEngine::isGameOver() {
    // CORRECT: Calling checkWin with char literals is valid.
    return checkWin("X").first || checkWin("O").first || checkDraw();
}
