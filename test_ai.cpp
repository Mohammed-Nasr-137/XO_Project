#include <gtest/gtest.h>
#include "ai.h"

// Helper to create a 3x3 empty board
Board EmptyBoard() {
    return Board(3, std::vector<char>(3, ' '));
}

TEST(AIAuditTest, LogsCorrectly) {
    AIAudit audit;
    audit.LogMove(1, 2, 10, 4, "Test move", 3);

    EXPECT_EQ(audit.GetLastExplanation(), "Test move");

    std::string json = audit.ExportLogAsJSON();
    EXPECT_NE(json.find("\"row\": 1"), std::string::npos);
    EXPECT_NE(json.find("\"col\": 2"), std::string::npos);
}

TEST(AIAuditTest, ResetClearsLog) {
    AIAudit audit;
    audit.LogMove(0, 0, 10, 3, "To be cleared", 1);
    audit.Reset();

    EXPECT_EQ(audit.GetLastExplanation(), "No moves recorded yet.");
    EXPECT_EQ(audit.ExportLogAsJSON(), "[\n]");
}

TEST(AITest_FriendAccess_Test, EvaluateBoardDetectsXWin) {
    AI ai;
    Board board = {
        {'X', 'X', 'X'},
        {'O', ' ', 'O'},
        {' ', ' ', ' '}
    };
    EXPECT_EQ(ai.EvaluateBoard(board, 'X', 'O'), 10);
}

TEST(AITest, EvaluateBoardDetectsOWin) {
    AI ai;
    Board board = {
        {'X', ' ', 'X'},
        {'O', 'O', 'O'},
        {' ', 'X', ' '}
    };
    EXPECT_EQ(ai.EvaluateBoard(board, 'X', 'O'), -10);
}

TEST(AITest, EvaluateBoardDetectsDraw) {
    AI ai;
    Board board = {
        {'X', 'O', 'X'},
        {'X', 'X', 'O'},
        {'O', 'X', 'O'}
    };
    EXPECT_EQ(ai.EvaluateBoard(board, 'X', 'O'), 0);
}

TEST(AITest, GetBestMoveEasyIsRandom) {
    AI ai;
    ai.SetDifficulty("easy");
    Board board = EmptyBoard();
    auto move = ai.GetBestMove(board, 'X');
    EXPECT_TRUE(board[move.first][move.second] == ' ');
}

TEST(AITest, GetBestMoveHardFindsWinningMove) {
    AI ai;
    ai.SetDifficulty("hard");
    Board board = {
        {'X', 'X', ' '},
        {'O', ' ', ' '},
        {' ', 'O', ' '}
    };
    auto move = ai.GetBestMove(board, 'X');
    // Expect winning move at (0, 2)
    EXPECT_EQ(move.first, 0);
    EXPECT_EQ(move.second, 2);
}

TEST(AITest, GenerateExplanation_Winning) {
    AI ai;
    Board before = {
        {'X', 'X', ' '},
        {'O', ' ', ' '},
        {' ', 'O', ' '}
    };
    Board after = before;
    after[0][2] = 'X';
    std::string explanation = ai.GenerateExplanation(before, after, 'X', 'O');
    EXPECT_NE(explanation.find("Winning"), std::string::npos);
}
