#include "include/game_logic.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

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

const std::vector<std::pair<Move, std::string>>&
GameEngine::get_moveHistory() const {
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

bool GameEngine::checkWin(std::string player) {
    int val = (player == "X") ? 1 : -1;
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((playerValue(board[i][0]) + playerValue(board[i][1]) +
             playerValue(board[i][2]) == 3 * val) ||
            (playerValue(board[0][i]) + playerValue(board[1][i]) +
             playerValue(board[2][i]) == 3 * val)) {
            return true;
        }
    }
    // Check diagonals
    if ((playerValue(board[0][0]) + playerValue(board[1][1]) +
         playerValue(board[2][2]) == 3 * val) ||
        (playerValue(board[0][2]) + playerValue(board[1][1]) +
         playerValue(board[2][0]) == 3 * val)) {
        return true;
    }
    return false;
}

bool GameEngine::checkDraw() {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;
            }
        }
    }
    // A draw is only true if the board is full AND no one has won
    return !checkWin("X") && !checkWin("O");
}

bool GameEngine::isGameOver() {
    return checkWin("X") || checkWin("O") || checkDraw();
}
