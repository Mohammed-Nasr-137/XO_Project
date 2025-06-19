#ifndef GAME_WRAPPER_H
#define GAME_WRAPPER_H
#include <vector>
#include <string>
#include <tuple>
#include "user_system.h"
#include "ai.h"
#include "game_logic.h"
// The GameWrapper class acts as a controller or facade, connecting the
// UI layer with the backend game logic, AI, and user database systems.
class GameWrapper
{
private:
    UserSystem  sys_;
    AI          ai_;
    GameEngine  game_;
    bool        is_single_mode_;
    std::string player1_;
    std::string player2_;
    std::string player1_symbol_;
    std::string player2_symbol_;
    std::string current_user_;
    std::string comment_;

    // Helper to get the move history in a simple format.
    std::vector<std::pair<int, std::string>> GetMoveHistory();
    // Helper to get the last AI move explanation.
    void GetComment();

public:
    // Constructor initializes the UserSystem with the database path.
    GameWrapper();
    // --- User Management ---
    bool Login_Wrapper(const std::string& username, const std::string& password);
    bool Register_Wrapper(const std::string& username, const std::string& password);
    // --- Game Flow ---
    void StartNewGame(const std::string& p1, const std::string& p2, bool is_single_mode, const std::string& ai_level, const std::string& chosen_symbol);
    bool MakeHumanMove(int position);
    pair<bool, int> MakeAIMove();
    void Undo();
    // --- Game State Checks ---
    std::pair<bool, std::string> CheckWinner();
    bool CheckTie();
    std::vector<std::vector<char>> GetBoard();
    char getCurrentUserSymbol();
    string getcurrent_user();
    // --- Database History/Stats ---
    bool SaveGameWithMoves(
        const std::string player1, // username1
        const std::string player2, // username2
        const std::string winner,  // winner symbol
        const std::vector<std::pair<int, std::string>> moves // pair of position and comment
        );
    std::vector<std::tuple<int, std::string, std::string, std::string>> GetGameHistory(const std::string& username);
    std::vector<std::pair<int, std::string>> LoadGameMovesWithComments(int game_id);
    std::tuple<int, int, int> GetHeadToHeadStats(const std::string& user1, const std::string& user2);
    std::tuple<int, int, int> GetHumanVsAIStats(const std::string& humanUser);
};
#endif
