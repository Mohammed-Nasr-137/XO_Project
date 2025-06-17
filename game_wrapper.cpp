#include "include/ai.h"
#include "include/game_logic.h"
#include "include/user_system.h"
#include "include/game_wrapper.h"

#include <string>
#include <utility>
#include <tuple>
#include <vector>

using std::pair;
using std::string;
using std::tuple;
using std::vector;

GameWrapper::GameWrapper() : sys_("game_db") {}

bool GameWrapper::Login_Wrapper(const string& username, const string& password) {
    // is called when login button is clicked
    return sys_.loginUser(username, password);
}

bool GameWrapper::Register_Wrapper(const string& username, const string& password) {
    // is called when register button is clicked
    return sys_.registerUser(username, password);
}

void GameWrapper::StartNewGame(const string& p1, const string& p2,
                               bool is_single_mode, const string& ai_level,
                               const string& chosen_symbol) {
    // is called at the start of a new game whether it's single or multi
    // (after signing in the 2nd user) or in case of reset button is clicked
    // called after a move is chosen
    // controls which player starts
    player1_ = p1;
    player2_ = p2;
    is_single_mode_ = is_single_mode;
    game_.Game_init();
    player1_symbol_ = chosen_symbol;
    player2_symbol_ = (chosen_symbol == "X") ? "O" : "X";
    current_user_ = "X";
    if (is_single_mode) {
        ai_.SetDifficulty(ai_level);
    }
}

bool GameWrapper::MakeHumanMove(int position) {
    // used by every human player
    bool success = game_.makeMove(position, "Human move");
    if (success) {
        current_user_ = (current_user_ == "X") ? "O" : "X";
    }
    return success;
}

pair<bool, int> GameWrapper::MakeAIMove() {
    // used by ai if single mode
    pair<int, int> ai_move = ai_.GetBestMove(
        game_.get_board(), game_.getCurrentPlayer());
    int position = 1 + ai_move.second + 3 * ai_move.first;
    bool success = game_.makeMove(position, comment_);
    if (success) {
        current_user_ = (current_user_ == "X") ? "O" : "X";
    }
    return {success, position};
}

void GameWrapper::Undo() {
    // is called when undo button is clicked
    if (is_single_mode_) {
        game_.undoMove();
        game_.undoMove();
    } else {
        game_.undoMove();
    }
}

pair<bool, string> GameWrapper::CheckWinner() {
    // returns pair of (if winner, winner symbol)
    string current_winner_move = (current_user_ == "X") ? "O" : "X";
    string current_winner_user = "";
    bool is_win = game_.checkWin(current_winner_move);
    pair<bool, string> p = {is_win, current_winner_move};
    /*if (is_win)
        {
            current_winner_user = (current_winner_move == player1_symbol_) ?
                player1_ : player2_;  // determine which user has won
        }*/
    return p;
}

bool GameWrapper::CheckTie() {
    return game_.checkDraw();
}

vector<vector<char>> GameWrapper::GetBoard() {
    return game_.get_board();
}

char GameWrapper::getCurrentUserSymbol() {
    return game_.getCurrentPlayer();
}

string GameWrapper::getcurrent_user() {
    return current_user_;
}

bool GameWrapper::SaveGameWithMoves(const string player1, const string player2,
                                    const string winner,
                                    const vector<pair<int, string>>& moves) {
    // used at the end of each game
    return sys_.saveGameWithMoves(player1, player2, winner, moves);
}

vector<tuple<int, string, string, string>>
GameWrapper::GetGameHistory(const string& username) {
    // given a username it returns a vector of tuples
    // (game-id, player1, player2, winner(as a username))
    // used when gamehistory is clicked
    return sys_.getGameHistory(username);
}

vector<pair<int, string>>
GameWrapper::LoadGameMovesWithComments(int game_id) {
    // given an id (linked to the replay button in the list)
    // returns pair of position and comments
    return sys_.loadGameMovesWithComments(game_id);
}

tuple<int, int, int> GameWrapper::GetHeadToHeadStats(
    const string& user1, const string& user2) {
    // given 2 users returns a tuple (wins1, wins2, ties)
    // used in the start of a multiplayer game
    return sys_.getHeadToHeadStats(user1, user2);
}

tuple<int, int, int> GameWrapper::GetHumanVsAIStats(
    const string& humanUser) {
    // given a user returns a tuple (human-wins, ai-wins, ties)
    // used in the start of a singleplayer game
    return sys_.getHumanVsAIStats(humanUser);
}
