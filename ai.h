#ifndef AI_H_
#define AI_H_

#include <vector>
#include <utility>
#include <string>

typedef std::vector<std::vector<char>> Board;

class AI {
 public:
  void SetDifficulty(const std::string& level);

  std::pair<int, int> GetBestMove(const Board& board, char ai_player);

 private:
  int Minimax(Board board, bool is_maximizing, char ai_player, char human_player, int depth, int alpha, int beta);
  int EvaluateBoard(const Board& board, char ai_player, char human_player);

  std::vector<std::pair<int, int>> GetLegalMoves(const Board& board);
  std::string difficulty_;
};

#endif

