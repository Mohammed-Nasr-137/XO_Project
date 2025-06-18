#include <gtest/gtest.h>
#include "ai.h"
#include <algorithm>
#include <set>

// Helper to create a 3x3 empty board
Board EmptyBoard() {
    return Board(3, std::vector<char>(3, ' '));
}

// Helper to create a board from a string representation
Board CreateBoard(const std::vector<std::string>& rows) {
    Board board(3, std::vector<char>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = rows[i][j];
        }
    }
    return board;
}

// ========== AIAudit Test Cases ==========

class AIAuditTest : public ::testing::Test {
protected:
    AIAudit audit;
};

TEST_F(AIAuditTest, EmptyLogReturnsCorrectMessage) {
    EXPECT_EQ(audit.GetLastExplanation(), "No moves recorded yet.");
}

TEST_F(AIAuditTest, ExportEmptyLogReturnsEmptyJSON) {
    std::string json = audit.ExportLogAsJSON();
    EXPECT_EQ(json, "[\n]");
}

TEST_F(AIAuditTest, LogSingleMoveAndExport) {
    audit.LogMove(2, 1, 15, 5, "Strategic corner move", 1);
    
    std::string json = audit.ExportLogAsJSON();
    EXPECT_NE(json.find("\"move_number\": 1"), std::string::npos);
    EXPECT_NE(json.find("\"row\": 2"), std::string::npos);
    EXPECT_NE(json.find("\"col\": 1"), std::string::npos);
    EXPECT_NE(json.find("\"score\": 15"), std::string::npos);
    EXPECT_NE(json.find("\"depth\": 5"), std::string::npos);
    EXPECT_NE(json.find("Strategic corner move"), std::string::npos);
}

TEST_F(AIAuditTest, LogMultipleMovesPreservesOrder) {
    audit.LogMove(0, 0, 5, 2, "First move", 1);
    audit.LogMove(1, 1, 8, 3, "Second move", 2);
    audit.LogMove(2, 2, 12, 4, "Third move", 3);
    
    std::string json = audit.ExportLogAsJSON();
    
    // Check that moves appear in correct order
    size_t first_pos = json.find("First move");
    size_t second_pos = json.find("Second move");
    size_t third_pos = json.find("Third move");
    
    EXPECT_LT(first_pos, second_pos);
    EXPECT_LT(second_pos, third_pos);
    EXPECT_EQ(audit.GetLastExplanation(), "Third move");
}

TEST_F(AIAuditTest, ResetAfterMultipleMovesWorks) {
    audit.LogMove(0, 0, 10, 3, "Move 1", 1);
    audit.LogMove(1, 1, 15, 4, "Move 2", 2);
    audit.Reset();
    
    EXPECT_EQ(audit.GetLastExplanation(), "No moves recorded yet.");
    
    // Add new move after reset
    audit.LogMove(2, 2, 20, 5, "New move", 1);
    EXPECT_EQ(audit.GetLastExplanation(), "New move");
}

TEST_F(AIAuditTest, JSONFormatValidation) {
    audit.LogMove(1, 2, -5, 1, "Test \"quoted\" move", 1);
    
    std::string json = audit.ExportLogAsJSON();
    
    // Check JSON structure
    EXPECT_EQ(json.front(), '[');
    EXPECT_EQ(json.back(), ']');
    EXPECT_NE(json.find("\"move_number\":"), std::string::npos);
    EXPECT_NE(json.find("\"row\":"), std::string::npos);
    EXPECT_NE(json.find("\"col\":"), std::string::npos);
    EXPECT_NE(json.find("\"score\":"), std::string::npos);
    EXPECT_NE(json.find("\"depth\":"), std::string::npos);
    EXPECT_NE(json.find("\"explanation\":"), std::string::npos);
}

// ========== AI Test Cases ==========

class AITest : public ::testing::Test {
protected:
    AI ai;
    
    void SetUp() override {
        ai.SetDifficulty("hard"); // Default to hard for most tests
    }
};

// Test EvaluateBoard functionality
TEST_F(AITest, EvaluateBoardDetectsXWinInRows) {
    std::vector<Board> winning_boards = {
        CreateBoard({"XXX", "O O", "   "}), // Row 0
        CreateBoard({"O O", "XXX", "   "}), // Row 1
        CreateBoard({"O O", "   ", "XXX"})  // Row 2
    };
    
    for (const auto& board : winning_boards) {
        EXPECT_EQ(ai.EvaluateBoard(board, 'X', 'O'), 10);
    }
}

TEST_F(AITest, EvaluateBoardDetectsXWinInColumns) {
    std::vector<Board> winning_boards = {
        CreateBoard({"XO ", "XO ", "X  "}), // Col 0
        CreateBoard({" XO", " XO", " X "}), // Col 1
        CreateBoard({"  X", " OX", " OX"})  // Col 2
    };
    
    for (const auto& board : winning_boards) {
        EXPECT_EQ(ai.EvaluateBoard(board, 'X', 'O'), 10);
    }
}

TEST_F(AITest, EvaluateBoardDetectsXWinInDiagonals) {
    Board main_diagonal = CreateBoard({"X O", " X ", "O X"});
    Board anti_diagonal = CreateBoard({"O X", " X ", "XO "});
    
    EXPECT_EQ(ai.EvaluateBoard(main_diagonal, 'X', 'O'), 10);
    EXPECT_EQ(ai.EvaluateBoard(anti_diagonal, 'X', 'O'), 10);
}

TEST_F(AITest, EvaluateBoardDetectsOWinScenarios) {
    Board o_wins = CreateBoard({"OXX", "OX ", "O  "});
    EXPECT_EQ(ai.EvaluateBoard(o_wins, 'X', 'O'), -10);
}

TEST_F(AITest, EvaluateBoardDetectsIncompleteGame) {
    Board incomplete = CreateBoard({"X O", " X ", "O  "});
    EXPECT_EQ(ai.EvaluateBoard(incomplete, 'X', 'O'), 0);
}

// Test GetLegalMoves functionality
TEST_F(AITest, GetLegalMovesOnEmptyBoard) {
    Board empty = EmptyBoard();
    auto moves = ai.GetLegalMoves(empty);
    
    EXPECT_EQ(moves.size(), 9);
    
    // Verify all positions are included
    std::set<std::pair<int, int>> move_set(moves.begin(), moves.end());
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_TRUE(move_set.count({i, j}) > 0);
        }
    }
}

TEST_F(AITest, GetLegalMovesOnPartialBoard) {
    Board partial = CreateBoard({"X O", " X ", "O  "});
    auto moves = ai.GetLegalMoves(partial);
    
    EXPECT_EQ(moves.size(), 5);
    
    std::set<std::pair<int, int>> expected = {{0,1}, {1,0}, {1,2}, {2,1}, {2,2}};
    std::set<std::pair<int, int>> actual(moves.begin(), moves.end());
    
    EXPECT_EQ(expected, actual);
}

TEST_F(AITest, GetLegalMovesOnFullBoard) {
    Board full = CreateBoard({"XOX", "OXO", "OXO"});
    auto moves = ai.GetLegalMoves(full);
    
    EXPECT_EQ(moves.size(), 0);
}

// Test AI Decision Making
TEST_F(AITest, AITakesImmediateWinOverBlock) {
    Board board = CreateBoard({"XX ", "OO ", "   "});
    auto move = ai.GetBestMove(board, 'X');
    
    // AI should complete its own winning line
    EXPECT_EQ(move.first, 0);
    EXPECT_EQ(move.second, 2);
}

TEST_F(AITest, AIBlocksOpponentWinWhenNoWinAvailable) {
    Board board = CreateBoard({"OO ", "X  ", " X "});
    auto move = ai.GetBestMove(board, 'X');
    
    // AI should block O's win
    EXPECT_EQ(move.first, 0);
    EXPECT_EQ(move.second, 2);
}

TEST_F(AITest, AICreatesWinningFork) {
    Board board = CreateBoard({"X  ", "   ", "  O"});
    // After AI plays center, it should be setting up multiple winning threats
    ai.GetBestMove(board, 'X');
    // This is more of a strategic test - actual fork detection would need more complex setup
}

// Test Difficulty Levels
TEST_F(AITest, EasyDifficultyMakesValidMoves) {
    ai.SetDifficulty("easy");
    Board board = CreateBoard({"X  ", "O  ", "   "});
    
    // Test multiple moves to ensure they're all valid
    for (int i = 0; i < 10; ++i) {
        auto move = ai.GetBestMove(board, 'X');
        EXPECT_TRUE(move.first >= 0 && move.first < 3);
        EXPECT_TRUE(move.second >= 0 && move.second < 3);
        EXPECT_EQ(board[move.first][move.second], ' ');
    }
}

TEST_F(AITest, MediumDifficultyBlocksImmediateThreats) {
    ai.SetDifficulty("medium");
    Board board = CreateBoard({"OO ", "X  ", "  X"});
    auto move = ai.GetBestMove(board, 'X');
    
    // Even on medium, should block immediate wins
    EXPECT_EQ(move.first, 0);
    EXPECT_EQ(move.second, 2);
}

TEST_F(AITest, HardDifficultyPlaysOptimally) {
    ai.SetDifficulty("hard");
    Board board = CreateBoard({"   ", " X ", "   "});
    auto move = ai.GetBestMove(board, 'O');
    
    // Against perfect play, O should take a corner
    EXPECT_TRUE((move.first == 0 && (move.second == 0 || move.second == 2)) ||
                (move.first == 2 && (move.second == 0 || move.second == 2)));
}

// Test GenerateExplanation functionality
TEST_F(AITest, GenerateExplanationDetectsWinningMove) {
    Board before = CreateBoard({"XX ", "OO ", "   "});
    Board after = before;
    after[0][2] = 'X';
    
    std::string explanation = ai.GenerateExplanation(before, after, 'X', 'O');
    EXPECT_NE(explanation.find("Winning move"), std::string::npos);
}

TEST_F(AITest, GenerateExplanationDetectsBlockingMove) {
    Board before = CreateBoard({"OO ", "X  ", "  X"});
    Board after = before;
    after[0][2] = 'X'; // Blocking move
    
    std::string explanation = ai.GenerateExplanation(before, after, 'X', 'O');
    EXPECT_NE(explanation.find("Blocked opponent"), std::string::npos);
}

TEST_F(AITest, GenerateExplanationDetectsCenterCapture) {
    Board before = CreateBoard({"X  ", "   ", "  O"});
    Board after = before;
    after[1][1] = 'X'; // Center capture
    
    std::string explanation = ai.GenerateExplanation(before, after, 'X', 'O');
    EXPECT_NE(explanation.find("center"), std::string::npos);
}

TEST_F(AITest, GenerateExplanationFallsBackToDefault) {
    Board before = CreateBoard({"XO ", "   ", "   "});
    Board after = before;
    after[2][2] = 'X'; // Random corner move
    
    std::string explanation = ai.GenerateExplanation(before, after, 'X', 'O');
    EXPECT_NE(explanation.find("Best evaluated move"), std::string::npos);
}

// Test Edge Cases
TEST_F(AITest, AIHandlesNearFullBoard) {
    Board board = CreateBoard({"XOX", "OXO", "  X"});
    auto move = ai.GetBestMove(board, 'O');
    
    // Should pick one of the two remaining spaces
    EXPECT_TRUE((move.first == 2 && move.second == 0) || 
                (move.first == 2 && move.second == 1));
}

TEST_F(AITest, AIHandlesSymmetricPositions) {
    Board board = CreateBoard({"   ", " X ", "   "});
    auto move = ai.GetBestMove(board, 'O');
    
    // Should pick a corner (all corners are equivalent)
    EXPECT_TRUE((move.first == 0 || move.first == 2) && 
                (move.second == 0 || move.second == 2));
}

// Integration test with audit
TEST_F(AITest, AIAuditIntegrationTest) {
    Board board = CreateBoard({"XX ", "OO ", "   "});
    auto move = ai.GetBestMove(board, 'X');
    
    std::string last_explanation = ai.audit_.GetLastExplanation();
    EXPECT_FALSE(last_explanation.empty());
    EXPECT_NE(last_explanation, "No moves recorded yet.");
    
    std::string json = ai.audit_.ExportLogAsJSON();
    EXPECT_NE(json.find("\"row\": " + std::to_string(move.first)), std::string::npos);
    EXPECT_NE(json.find("\"col\": " + std::to_string(move.second)), std::string::npos);
}