#include <gtest/gtest.h>
#include "game_logic.h"

class GameEngineTest : public ::testing::Test {
protected:
    void SetUp() override {
        game.Game_init();
    }
    
    GameEngine game;
};

// Test Game Initialization
TEST_F(GameEngineTest, GameInitializesCorrectly) {
    Board board = game.get_board();
    
    // Check board is 3x3 and empty
    ASSERT_EQ(board.size(), 3);
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(board[i].size(), 3);
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(board[i][j], ' ');
        }
    }
    
    // Check initial player is X
    EXPECT_EQ(game.getCurrentPlayer(), 'X');
    EXPECT_EQ(game.getOpponentPlayer(), 'O');
    
    // Check move history is empty
    EXPECT_TRUE(game.get_moveHistory().empty());
    
    // Check game is not over initially
    EXPECT_FALSE(game.isGameOver());
}

// Test Valid Move Validation
TEST_F(GameEngineTest, ValidMoveValidation) {
    // Valid positions (1-9)
    for (int pos = 1; pos <= 9; ++pos) {
        EXPECT_TRUE(game.isValidMove(pos));
    }
    
    // Invalid positions
    EXPECT_FALSE(game.isValidMove(0));
    EXPECT_FALSE(game.isValidMove(10));
    EXPECT_FALSE(game.isValidMove(-1));
    EXPECT_FALSE(game.isValidMove(100));
}

TEST_F(GameEngineTest, InvalidMoveOnOccupiedCell) {
    // Make a move at position 1
    ASSERT_TRUE(game.makeMove(1, "First move"));
    
    // Position 1 should now be invalid
    EXPECT_FALSE(game.isValidMove(1));
    
    // Other positions should still be valid
    EXPECT_TRUE(game.isValidMove(2));
    EXPECT_TRUE(game.isValidMove(9));
}

// Test Move Making
TEST_F(GameEngineTest, MakeMoveSuccessfully) {
    EXPECT_TRUE(game.makeMove(1, "X plays center-left"));
    
    Board board = game.get_board();
    EXPECT_EQ(board[0][0], 'X');
    EXPECT_EQ(game.getCurrentPlayer(), 'O');
    
    auto history = game.get_moveHistory();
    ASSERT_EQ(history.size(), 1);
    EXPECT_EQ(history[0].first.position, 1);
    EXPECT_EQ(history[0].first.player, 'X');
    EXPECT_EQ(history[0].second, "X plays center-left");
}

TEST_F(GameEngineTest, MakeInvalidMove) {
    // Try invalid position
    EXPECT_FALSE(game.makeMove(0, "Invalid move"));
    EXPECT_FALSE(game.makeMove(10, "Invalid move"));
    
    // Board should remain unchanged
    Board board = game.get_board();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(board[i][j], ' ');
        }
    }
    
    // Current player should remain X
    EXPECT_EQ(game.getCurrentPlayer(), 'X');
    EXPECT_TRUE(game.get_moveHistory().empty());
}

TEST_F(GameEngineTest, AlternatingPlayers) {
    EXPECT_EQ(game.getCurrentPlayer(), 'X');
    
    game.makeMove(1, "X move");
    EXPECT_EQ(game.getCurrentPlayer(), 'O');
    
    game.makeMove(2, "O move");
    EXPECT_EQ(game.getCurrentPlayer(), 'X');
    
    game.makeMove(3, "X move");
    EXPECT_EQ(game.getCurrentPlayer(), 'O');
}

// Test Undo Functionality
TEST_F(GameEngineTest, UndoMove) {
    // Make some moves
    game.makeMove(1, "First move");
    game.makeMove(2, "Second move");
    
    EXPECT_EQ(game.getCurrentPlayer(), 'X');
    EXPECT_EQ(game.get_moveHistory().size(), 2);
    
    // Undo last move
    EXPECT_TRUE(game.undoMove());
    EXPECT_EQ(game.getCurrentPlayer(), 'O');
    EXPECT_EQ(game.get_moveHistory().size(), 1);
    
    Board board = game.get_board();
    EXPECT_EQ(board[0][0], 'X');  // First move still there
    EXPECT_EQ(board[0][1], ' ');  // Second move undone
}

TEST_F(GameEngineTest, UndoEmptyHistory) {
    EXPECT_FALSE(game.undoMove());
    EXPECT_EQ(game.getCurrentPlayer(), 'X');
    EXPECT_TRUE(game.get_moveHistory().empty());
}

// Test Win Conditions - Rows
TEST_F(GameEngineTest, CheckWinHorizontalRows) {
    // Test all three rows for X wins
    game.Game_init();
    game.makeMove(1, ""); game.makeMove(4, "");  // X: (0,0), O: (1,0)
    game.makeMove(2, ""); game.makeMove(5, "");  // X: (0,1), O: (1,1)
    game.makeMove(3, "");                        // X: (0,2) - X wins row 0
    EXPECT_TRUE(game.checkWin("X"));
    EXPECT_FALSE(game.checkWin("O"));
    
    game.Game_init();
    game.makeMove(4, ""); game.makeMove(1, "");  // X: (1,0), O: (0,0)
    game.makeMove(5, ""); game.makeMove(2, "");  // X: (1,1), O: (0,1)
    game.makeMove(6, "");                        // X: (1,2) - X wins row 1
    EXPECT_TRUE(game.checkWin("X"));
    
    game.Game_init();
    game.makeMove(7, ""); game.makeMove(1, "");  // X: (2,0), O: (0,0)
    game.makeMove(8, ""); game.makeMove(2, "");  // X: (2,1), O: (0,1)
    game.makeMove(9, "");                        // X: (2,2) - X wins row 2
    EXPECT_TRUE(game.checkWin("X"));
}

// Test Win Conditions - Columns
TEST_F(GameEngineTest, CheckWinVerticalColumns) {
    // Test first column for O wins
    game.Game_init();
    game.makeMove(2, ""); game.makeMove(1, "");  // X: (0,1), O: (0,0)
    game.makeMove(3, ""); game.makeMove(4, "");  // X: (0,2), O: (1,0)
    game.makeMove(5, ""); game.makeMove(7, "");  // X: (1,1), O: (2,0) - O wins column 0
    EXPECT_TRUE(game.checkWin("O"));
    EXPECT_FALSE(game.checkWin("X"));
    
    // Test middle column
    game.Game_init();
    game.makeMove(1, ""); game.makeMove(2, "");  // X: (0,0), O: (0,1)
    game.makeMove(3, ""); game.makeMove(5, "");  // X: (0,2), O: (1,1)
    game.makeMove(4, ""); game.makeMove(8, "");  // X: (1,0), O: (2,1) - O wins column 1
    EXPECT_TRUE(game.checkWin("O"));
    
    // Test last column
    game.Game_init();
    game.makeMove(1, ""); game.makeMove(3, "");  // X: (0,0), O: (0,2)
    game.makeMove(2, ""); game.makeMove(6, "");  // X: (0,1), O: (1,2)
    game.makeMove(4, ""); game.makeMove(9, "");  // X: (1,0), O: (2,2) - O wins column 2
    EXPECT_TRUE(game.checkWin("O"));
}

// Test Win Conditions - Diagonals
TEST_F(GameEngineTest, CheckWinDiagonals) {
    // Test main diagonal (top-left to bottom-right)
    game.Game_init();
    game.makeMove(1, ""); game.makeMove(2, "");  // X: (0,0), O: (0,1)
    game.makeMove(5, ""); game.makeMove(3, "");  // X: (1,1), O: (0,2)
    game.makeMove(9, "");                        // X: (2,2) - X wins main diagonal
    EXPECT_TRUE(game.checkWin("X"));
    
    // Test anti-diagonal (top-right to bottom-left)
    game.Game_init();
    game.makeMove(3, ""); game.makeMove(1, "");  // X: (0,2), O: (0,0)
    game.makeMove(5, ""); game.makeMove(2, "");  // X: (1,1), O: (0,1)
    game.makeMove(7, "");                        // X: (2,0) - X wins anti-diagonal
    EXPECT_TRUE(game.checkWin("X"));
}

// Test Draw Conditions
TEST_F(GameEngineTest, CheckDraw) {
    // Fill board without winner: X O O / O X X / X X O
    game.makeMove(1, ""); // X
    game.makeMove(2, ""); // O
    game.makeMove(5, ""); // X
    game.makeMove(3, ""); // O
    game.makeMove(7, ""); // X
    game.makeMove(4, ""); // O
    game.makeMove(8, ""); // X
    game.makeMove(9, ""); // O
    game.makeMove(6, ""); // X
    
    EXPECT_FALSE(game.checkWin("X"));
    EXPECT_FALSE(game.checkWin("O"));
    EXPECT_TRUE(game.checkDraw());
    EXPECT_TRUE(game.isGameOver());
}

TEST_F(GameEngineTest, NotDrawWhenBoardNotFull) {
    game.makeMove(1, "");
    game.makeMove(2, "");
    
    EXPECT_FALSE(game.checkDraw());
    EXPECT_FALSE(game.isGameOver());
}

TEST_F(GameEngineTest, NotDrawWhenSomeoneWins) {
    // Create winning condition for X
    game.makeMove(1, ""); game.makeMove(4, "");
    game.makeMove(2, ""); game.makeMove(5, "");
    game.makeMove(3, ""); // X wins
    
    EXPECT_TRUE(game.checkWin("X"));
    EXPECT_FALSE(game.checkDraw());
    EXPECT_TRUE(game.isGameOver());
}

// Test Game Over Conditions
TEST_F(GameEngineTest, GameOverOnWin) {
    // Create X win
    game.makeMove(1, ""); game.makeMove(4, "");
    game.makeMove(2, ""); game.makeMove(5, "");
    game.makeMove(3, ""); // X wins
    
    EXPECT_TRUE(game.isGameOver());
}

TEST_F(GameEngineTest, GameOverOnDraw) {
    // Create draw scenario
    game.makeMove(1, ""); game.makeMove(2, "");
    game.makeMove(3, ""); game.makeMove(4, "");
    game.makeMove(5, ""); game.makeMove(6, "");
    game.makeMove(7, ""); game.makeMove(8, "");
    game.makeMove(9, "");
    
    EXPECT_TRUE(game.isGameOver());
}

TEST_F(GameEngineTest, GameNotOverInProgress) {
    game.makeMove(1, "");
    game.makeMove(2, "");
    
    EXPECT_FALSE(game.isGameOver());
}

// Test Position to Coordinate Conversion
TEST_F(GameEngineTest, PositionMapping) {
    // Test that positions map correctly to board coordinates
    game.makeMove(1, ""); // Should be (0,0)
    game.makeMove(2, ""); // Should be (0,1)
    game.makeMove(3, ""); // Should be (0,2)
    game.makeMove(4, ""); // Should be (1,0)
    game.makeMove(5, ""); // Should be (1,1)
    game.makeMove(6, ""); // Should be (1,2)
    game.makeMove(7, ""); // Should be (2,0)
    game.makeMove(8, ""); // Should be (2,1)
    game.makeMove(9, ""); // Should be (2,2)
    
    Board board = game.get_board();
    EXPECT_EQ(board[0][0], 'X'); // Position 1
    EXPECT_EQ(board[0][1], 'O'); // Position 2
    EXPECT_EQ(board[0][2], 'X'); // Position 3
    EXPECT_EQ(board[1][0], 'O'); // Position 4
    EXPECT_EQ(board[1][1], 'X'); // Position 5
    EXPECT_EQ(board[1][2], 'O'); // Position 6
    EXPECT_EQ(board[2][0], 'X'); // Position 7
    EXPECT_EQ(board[2][1], 'O'); // Position 8
    EXPECT_EQ(board[2][2], 'X'); // Position 9
}

// Test Move History
TEST_F(GameEngineTest, MoveHistoryTracking) {
    game.makeMove(1, "First move");
    game.makeMove(5, "Center move");
    game.makeMove(9, "Corner move");
    
    auto history = game.get_moveHistory();
    ASSERT_EQ(history.size(), 3);
    
    EXPECT_EQ(history[0].first.position, 1);
    EXPECT_EQ(history[0].first.player, 'X');
    EXPECT_EQ(history[0].second, "First move");
    
    EXPECT_EQ(history[1].first.position, 5);
    EXPECT_EQ(history[1].first.player, 'O');
    EXPECT_EQ(history[1].second, "Center move");
    
    EXPECT_EQ(history[2].first.position, 9);
    EXPECT_EQ(history[2].first.player, 'X');
    EXPECT_EQ(history[2].second, "Corner move");
}
