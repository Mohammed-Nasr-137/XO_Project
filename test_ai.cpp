#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "include/ai.h"

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
    EXPECT_EQ(board[move.first][move.second], ' ');
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

TEST(AITest, BlocksOpponentsWinningMove) {
    AI ai;
    ai.SetDifficulty("hard");
    Board board = {
        {'O', 'O', ' '},
        {'X', ' ', ' '},
        {' ', 'X', ' '}
    };
    auto move = ai.GetBestMove(board, 'X');
    EXPECT_EQ(move.first, 0);
    EXPECT_EQ(move.second, 2);  // Block O from winning
}

TEST(AITest, MediumDepthPreventsImmediateLossButMayMissFork) {
    AI ai;
    ai.SetDifficulty("medium");
    Board board = {
        {'O', ' ', ' '},
        {' ', 'X', ' '},
        {' ', ' ', 'O'}
    };
    auto move = ai.GetBestMove(board, 'X');
    // May capture center or block immediate threat
    EXPECT_TRUE((move.first == 0 && move.second == 1) ||
                (move.first == 2 && move.second == 1));
}

TEST(AIAuditTest, MultipleMovesLogging) {
    AIAudit audit;
    audit.LogMove(0, 0, 5, 2, "Test move 1", 1);
    audit.LogMove(1, 1, 10, 3, "Test move 2", 2);

    std::string json = audit.ExportLogAsJSON();
    EXPECT_NE(json.find("\"move_number\": 1"), std::string::npos);
    EXPECT_NE(json.find("\"move_number\": 2"), std::string::npos);
    EXPECT_NE(json.find("Test move 2"), std::string::npos);
}

TEST(AITest, GenerateExplanationBlocksWinningMove) {
    AI ai;
    Board before = {
        {'O', 'O', ' '},
        {'X', ' ', ' '},
        {' ', 'X', ' '}};
    Board after = before;
    after[0][2] = 'X';  // Blocking O's win
    std::string explanation = ai.GenerateExplanation(before, after, 'X', 'O');
    EXPECT_NE(explanation.find("Blocked opponent"), std::string::npos);
}

TEST(AITest, EasyModeRandomMovesDiffer) {
    AI ai;
    ai.SetDifficulty("easy");
    Board board = EmptyBoard();
    auto move1 = ai.GetBestMove(board, 'X');
    auto move2 = ai.GetBestMove(board, 'X');
    // There's a chance moves differ due to randomness
    EXPECT_FALSE(move1.first == move2.first && move1.second == move2.second);
}
