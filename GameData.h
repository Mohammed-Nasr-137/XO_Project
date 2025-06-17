#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QString>
#include "game_wrapper.h"
#include <vector>
// Forward-declare the GameWrapper class to avoid circular includes
// class GameWrapper;

// Singleton class to hold global application state.
class GameData {
public:
    // Accessor for the singleton instance.
    static GameData& instance() {
        static GameData _instance;
        return _instance;
    }

    // Global pointer to the main game controller.
    // This allows any part of the UI to access the game logic.
    GameWrapper controller;

    // --- UI State Variables ---
    QString firstPlayer;
    QString secondPlayer;
    QString P1turn;
    QString p1_move;
    QString Anotherturn;
    QString mode;
    QString level;
    string ai_difficulty;
    bool tracker = true;
    bool box_1;
    bool box_2;
    vector<vector<char>> gui_board = vector<vector<char>>(3, std::vector<char>(3, ' '));
    string current_player;
    // bool is_over = false;
    // QString winner;
    pair<bool, string> win_result = {false, ""};   // <is_win, winner_move>
    bool is_tie = false;
    bool is_over = false;
    bool is_ai_turn;

private:
    // Private constructor to enforce the singleton pattern.
    GameData() {}
};

#endif // GAMEDATA_H
