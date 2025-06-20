#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QString>
#include "game_wrapper.h"
#include <vector>
#include <QApplication>
#include <QMessageBox>
#include "gameboard.h"



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
    bool is_p1_starts;
    // bool is_over = false;
    // QString winner;
    tuple<bool, string, int> win_result = {false, "", 0};   // <is_win, winner_move>
    bool is_tie = false;
    bool is_over = false;
    bool is_ai_turn;
    vector<pair<int, string>> stack_last_played_pos;
    QPushButton* last_played_button;

    string x_player_history, o_player_history, winner_history;
    vector<pair<int, string>> moves_history; // at the last window
    Gameboard* gameboard_end;

private:
    // Private constructor to enforce the singleton pattern.
    GameData() {}
};

#endif // GAMEDATA_H
