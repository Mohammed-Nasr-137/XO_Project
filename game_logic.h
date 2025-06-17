#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <string>
#include <utility>
#include "ai.h"

// Defines a type alias for the game board for cleaner code.
using Board = std::vector<std::vector<char>>;



// Represents a single move in the game.
struct Move {
    int position;
    char player;
};

// Manages the core state and rules of the Tic-Tac-Toe game.
class GameEngine {
private:
    Board board;
    char currentPlayer;
    std::vector<std::pair<Move, std::string>> moveHistory;

    // Helper to convert player characters to numerical values for evaluation.
    int playerValue(char cell);

public:
    // Initializes the game board and state for a new game.
    void Game_init();

    // Returns the current state of the game board.
    Board get_board() const;

    // Returns the move history with associated comments.
    const std::vector<std::pair<Move, std::string>>& get_moveHistory() const;

    // Returns the character of the current player.
    char getCurrentPlayer() const;

    // Returns the character of the opponent.
    char getOpponentPlayer() const;

    // Checks if a move at the given position is valid.
    bool isValidMove(int position);

    // Attempts to make a move on the board.
    bool makeMove(int position, const std::string& comment);

    // Undoes the last move made.
    bool undoMove();

    // Checks if the specified player has won.
    // CORRECT: Takes a 'char' which is more efficient and avoids reference errors.
    bool checkWin(std::string player);

    // Checks if the game has ended in a draw.
    bool checkDraw();

    // Checks if the game is over (win or draw).
    bool isGameOver();
};

#endif // GAME_LOGIC_H
