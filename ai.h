#ifndef AI_H_
#define AI_H_

#include <vector>
#include <utility>
#include <string>
#include <map>

typedef std::vector<std::vector<char>> Board;


class AIAudit {
  public:
   void LogMove(int row, int col, int score, int depth, const std::string& explanation, int move_number);
   std::string GetLastExplanation() const;
   std::string ExportLogAsJSON() const;
   void Reset();
 
  private:
   struct MoveLog {
     int row;
     int col;
     int score;
     int depth;
     std::string explanation;
     int move_number;
   };
 
   std::vector<MoveLog> log_;
 };


class AI {
 public:
  void SetDifficulty(const std::string& level);
  std::pair<int, int> GetBestMove(const Board& board, char ai_player);
  AIAudit audit_;

 private:
  int Minimax(Board board, bool is_maximizing, char ai_player, char human_player, int depth, int alpha, int beta, int max_depth);
  int EvaluateBoard(const Board& board, char ai_player, char human_player);
  std::string AI::GenerateExplanation(const Board& board_before, const Board& board_after, char ai_player, char human_player);

  std::vector<std::pair<int, int>> GetLegalMoves(const Board& board);
  std::string difficulty_;
};

#endif

