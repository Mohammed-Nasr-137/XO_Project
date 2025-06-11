#include "ai.h"
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

void AI::SetDifficulty(const string& level) {
    difficulty_ = level;
    srand(static_cast<unsigned int>(time(nullptr)));
}

vector<pair<int, int>> AI::GetLegalMoves(const Board& board) {
    vector<pair<int, int>> moves;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == ' ') {
                moves.push_back({row, col});
            }
        }
    }
    return moves;
}

int AI::EvaluateBoard(const Board& board, char ai_player, char human_player) {
    vector<vector<int>> board_nums(3, vector<int>(3));
    map<char, int> symbol_to_value = {
        {ai_player, 1},
        {human_player, 4},
        {' ', 0}
    };
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            board_nums[row][col] = symbol_to_value[board[row][col]];
        }
    }
    // Rows
    for (int i = 0; i < 3; ++i) {
        int sum = board_nums[i][0] + board_nums[i][1] + board_nums[i][2];
        if (sum == 3) return +10;
        if (sum == 12) return -10;
    }

    // Columns
    for (int i = 0; i < 3; ++i) {
        int sum = board_nums[0][i] + board_nums[1][i] + board_nums[2][i];
        if (sum == 3) return +10;
        if (sum == 12) return -10;
    }

    // Diagonals
    int d1 = board_nums[0][0] + board_nums[1][1] + board_nums[2][2];
    int d2 = board_nums[0][2] + board_nums[1][1] + board_nums[2][0];
    if (d1 == 3 || d2 == 3) return +10;
    if (d1 == 12 || d2 == 12) return -10;

    return 0;
}

void AI::LogMinimaxMove(bool is_maximizing, int depth, const std::string& message, std::pair<int, int> move) const {
    std::string indent(depth * 2, ' ');  // 2 spaces per depth level
    std::string player = is_maximizing ? "MAX" : "MIN";

    if (move.first != -1 && move.second != -1) {
        cout << indent << player << ": " << message << " (" << move.first << "," << move.second << ") at depth " << depth << endl;
    } else {
        cout << indent << player << ": " << message << " at depth " << depth << endl;
    }
}


int AI::Minimax(Board board, bool is_maximizing, char ai_player, char human_player,
    int depth, int alpha, int beta, int max_depth) {

    int score = EvaluateBoard(board, ai_player, human_player);
    if (score == 10 || score == -10) {
        // LogMinimaxMove(is_maximizing, depth, "Terminal node: Score = " + std::to_string(score - depth)); 
        return score - depth;
    }
    if (GetLegalMoves(board).empty()) {
        // LogMinimaxMove(is_maximizing, depth, "Draw");
        return 0;
    }

    if (depth >= max_depth) {
        // LogMinimaxMove(is_maximizing, depth, "Max depth reached");
        return 0;
    }
    // AI turn
    if (is_maximizing) {
        int best = numeric_limits<int>::min();
        for (const auto& move : GetLegalMoves(board)) {
            board[move.first][move.second] = ai_player;
            // LogMinimaxMove(true, depth, "Trying move", move);

            int val = Minimax(board, false, ai_player, human_player,
                              depth + 1, alpha, beta, max_depth);

            best = max(best, val);
            alpha = max(alpha, best);
            board[move.first][move.second] = ' ';
            if (beta <= alpha) {
                // LogMinimaxMove(true, depth, "Alpha-Beta Prune");
                break;
            }
        }
        // LogMinimaxMove(true, depth, "Best score = " + std::to_string(best));
        return best;
    } 
    // Human turn
    else {
        int best = numeric_limits<int>::max();
        for (const auto& move : GetLegalMoves(board)) {
            board[move.first][move.second] = human_player;
            // LogMinimaxMove(false, depth, "Trying move", move);
            
            int val = Minimax(board, true, ai_player, human_player,
                              depth + 1, alpha, beta, max_depth);

            best = min(best, val);
            beta = min(beta, best);
            board[move.first][move.second] = ' ';
            if (beta <= alpha) {
                // LogMinimaxMove(false, depth, "Alpha-Beta Prune");
                break;
            }
        }
        // LogMinimaxMove(false, depth, "Best score = " + std::to_string(best));
        return best;
    }
}

string AI::GenerateExplanation(const Board& board_before, const Board& board_after, char ai_player, char human_player) {
    // 1. Immediate win?
    if (EvaluateBoard(board_after, ai_player, human_player) == 10) {
        return "Winning move — immediate victory!";
    }

    // 2. Blocked opponent’s winning move?
    auto opponent_moves = GetLegalMoves(board_before);
    for (const auto& move : opponent_moves) {
        Board temp = board_before;
        temp[move.first][move.second] = human_player;
        if (EvaluateBoard(temp, ai_player, human_player) == -10) {
            if (board_after[move.first][move.second] == ai_player) {
                return "Blocked opponent's win at (" + to_string(move.first) + ", " + to_string(move.second) + ")";
            }
        }
    }

    // 3. Center capture
    if (board_before[1][1] == ' ' && board_after[1][1] == ai_player) {
        return "Captured center to control the board.";
    }

    // 4. Fork creation
    int winning_paths = 0;
    auto ai_moves = GetLegalMoves(board_after);
    for (const auto& move : ai_moves) {
        Board temp = board_after;
        temp[move.first][move.second] = ai_player;
        if (EvaluateBoard(temp, ai_player, human_player) == 10) {
            winning_paths++;
        }
    }
    if (winning_paths >= 2) {
        return "Created a fork — multiple winning threats!";
    }


    // 5. Default explanation
    return "Best evaluated move based on future outcomes.";
}


pair<int, int> AI::GetBestMove(const Board& board, char ai_player) {
    char human_player = (ai_player == 'X') ? 'O' : 'X';
    auto legal_moves = GetLegalMoves(board);
    int move_number = 0;
    if (difficulty_ == "easy") {
        auto chosen = legal_moves[rand() % legal_moves.size()];
        audit_.LogMove(chosen.first, chosen.second, 0, 0, "Random move (easy mode)", 0);
        return chosen;
    }

    int best_score = numeric_limits<int>::min();
    pair<int, int> best_move = {-1, -1};
    int max_depth = (difficulty_ == "medium") ? 1 : 3; // medium = shallow search

    for (const auto& move : legal_moves) {
        Board temp = board;
        temp[move.first][move.second] = ai_player;

        int score = Minimax(temp, false, ai_player, human_player, 1, -1000, 1000, max_depth);
        if (score > best_score) {
            best_score = score;
            best_move = move;
        }

        ++move_number;
    }
    Board temp = board;
    temp[best_move.first][best_move.second] = ai_player;
    string explanation = GenerateExplanation(board, temp, ai_player, human_player);
    audit_.LogMove(best_move.first, best_move.second, best_score, max_depth,
                  explanation, move_number);
    return best_move;
}

void AIAudit::LogMove(int row, int col, int score, int depth, const string& explanation, int move_number) {
    MoveLog entry = {row, col, score, depth, explanation, move_number};
    log_.push_back(entry);
}

string AIAudit::GetLastExplanation() const {
    if (log_.empty()) {
        return "No moves recorded yet.";
    }
    return log_.back().explanation;
}

string AIAudit::ExportLogAsJSON() const {
    string json = "[\n";
    for (size_t i = 0; i < log_.size(); ++i) {
        const auto& move = log_[i];
        json += "  {\n";
        json += "    \"move_number\": " + to_string(move.move_number) + ",\n";
        json += "    \"row\": " + to_string(move.row) + ",\n";
        json += "    \"col\": " + to_string(move.col) + ",\n";
        json += "    \"score\": " + to_string(move.score) + ",\n";
        json += "    \"depth\": " + to_string(move.depth) + ",\n";
        json += "    \"explanation\": \"" + move.explanation + "\"\n";
        json += "  }";
        if (i != log_.size() - 1) json += ",";
        json += "\n";
    }
    json += "]";
    return json;
}

void AIAudit::Reset() {
    log_.clear();
}
