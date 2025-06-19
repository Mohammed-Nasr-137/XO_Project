#include <gtest/gtest.h>
#include <filesystem>
#include "game_wrapper.h"

using namespace std;

class GameWrapperTest : public ::testing::Test {
protected:
    void SetUp() override {
        wrapper = make_unique<GameWrapper>();
    }
    
    unique_ptr<GameWrapper> wrapper;
    
    string CreateUniqueUser() {
        return "user_" + to_string(time(nullptr) + rand());
    }
};

// Authentication Tests
TEST_F(GameWrapperTest, RegisterNewUser) {
    EXPECT_TRUE(wrapper->Register_Wrapper(CreateUniqueUser(), "pass123"));
}

TEST_F(GameWrapperTest, RegisterDuplicateUserFails) {
    string user = CreateUniqueUser();
    wrapper->Register_Wrapper(user, "pass");
    EXPECT_FALSE(wrapper->Register_Wrapper(user, "pass"));
}

TEST_F(GameWrapperTest, LoginValidUser) {
    string user = CreateUniqueUser();
    wrapper->Register_Wrapper(user, "pass");
    EXPECT_TRUE(wrapper->Login_Wrapper(user, "pass"));
}

TEST_F(GameWrapperTest, LoginInvalidUser) {
    EXPECT_FALSE(wrapper->Login_Wrapper("nonexistent", "wrong"));
}

// Game Initialization Tests
TEST_F(GameWrapperTest, StartGameMultiplayer) {
    wrapper->StartNewGame("Alice", "Bob", false, "", "X");
    auto board = wrapper->GetBoard();
    
    EXPECT_EQ(board.size(), 3);
    EXPECT_EQ(board[0][0], ' ');
    EXPECT_EQ(wrapper->getCurrentUserSymbol(), 'X');
}

TEST_F(GameWrapperTest, StartGameSinglePlayer) {
    wrapper->StartNewGame("Human", "AI", true, "easy", "O");
    EXPECT_EQ(wrapper->getCurrentUserSymbol(), 'X');
}

// Move Tests
TEST_F(GameWrapperTest, ValidHumanMove) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    EXPECT_TRUE(wrapper->MakeHumanMove(5));
    
    auto board = wrapper->GetBoard();
    EXPECT_EQ(board[1][1], 'X');
    EXPECT_EQ(wrapper->getCurrentUserSymbol(), 'O');
}

TEST_F(GameWrapperTest, InvalidHumanMove) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    EXPECT_FALSE(wrapper->MakeHumanMove(0));
    EXPECT_FALSE(wrapper->MakeHumanMove(10));
}

TEST_F(GameWrapperTest, OccupiedPositionMove) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    wrapper->MakeHumanMove(1);
    EXPECT_FALSE(wrapper->MakeHumanMove(1));
}

TEST_F(GameWrapperTest, AIMove) {
    wrapper->StartNewGame("Human", "AI", true, "easy", "X");
    wrapper->MakeHumanMove(1);
    
    auto result = wrapper->MakeAIMove();
    EXPECT_TRUE(result.first);
    EXPECT_GE(result.second, 1);
    EXPECT_LE(result.second, 9);
}

// Win Detection Tests
TEST_F(GameWrapperTest, HorizontalWin) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    wrapper->MakeHumanMove(1); // X
    wrapper->MakeHumanMove(4); // O
    wrapper->MakeHumanMove(2); // X
    wrapper->MakeHumanMove(5); // O
    wrapper->MakeHumanMove(3); // X wins
    
    auto winner = wrapper->CheckWinner();
    EXPECT_TRUE(get<0>(winner));
    EXPECT_EQ(get<1>(winner), "X");
}

TEST_F(GameWrapperTest, VerticalWin) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    wrapper->MakeHumanMove(1); // X
    wrapper->MakeHumanMove(2); // O
    wrapper->MakeHumanMove(4); // X
    wrapper->MakeHumanMove(5); // O
    wrapper->MakeHumanMove(7); // X wins
    
    auto winner = wrapper->CheckWinner();
    EXPECT_TRUE(get<0>(winner));
    EXPECT_EQ(get<1>(winner), "X");
}

TEST_F(GameWrapperTest, DiagonalWin) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    wrapper->MakeHumanMove(1); // X
    wrapper->MakeHumanMove(2); // O
    wrapper->MakeHumanMove(5); // X
    wrapper->MakeHumanMove(3); // O
    wrapper->MakeHumanMove(9); // X wins
    
    auto winner = wrapper->CheckWinner();
    EXPECT_TRUE(get<0>(winner));
    EXPECT_EQ(get<1>(winner), "X");
}

TEST_F(GameWrapperTest, TieGame) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    // Create tie: X O X / O X X / O X O
    wrapper->MakeHumanMove(1); wrapper->MakeHumanMove(2); wrapper->MakeHumanMove(3);
    wrapper->MakeHumanMove(4); wrapper->MakeHumanMove(5); wrapper->MakeHumanMove(7);
    wrapper->MakeHumanMove(6); wrapper->MakeHumanMove(9); wrapper->MakeHumanMove(8);
    
    EXPECT_TRUE(wrapper->CheckTie());
}

// Undo Tests
TEST_F(GameWrapperTest, UndoMove) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    wrapper->MakeHumanMove(5);
    
    wrapper->Undo();
    auto board = wrapper->GetBoard();
    EXPECT_EQ(board[1][1], ' ');
    EXPECT_EQ(wrapper->getCurrentUserSymbol(), 'X');
}

// Database Tests
TEST_F(GameWrapperTest, SaveGame) {
    string user1 = CreateUniqueUser();
    string user2 = CreateUniqueUser();
    wrapper->Register_Wrapper(user1, "pass");
    wrapper->Register_Wrapper(user2, "pass");
    
    vector<pair<int, string>> moves = {{1, "move1"}, {2, "move2"}};
    EXPECT_TRUE(wrapper->SaveGameWithMoves(user1, user2, "X", moves));
}

TEST_F(GameWrapperTest, GetGameHistory) {
    string user = CreateUniqueUser();
    wrapper->Register_Wrapper(user, "pass");
    
    vector<pair<int, string>> moves = {{1, "move"}};
    wrapper->SaveGameWithMoves(user, "opponent", "X", moves);
    
    auto history = wrapper->GetGameHistory(user);
    EXPECT_GE(history.size(), 1);
}

TEST_F(GameWrapperTest, HeadToHeadStats) {
    string user1 = CreateUniqueUser();
    string user2 = CreateUniqueUser();
    wrapper->Register_Wrapper(user1, "pass");
    wrapper->Register_Wrapper(user2, "pass");
    
    vector<pair<int, string>> moves = {{1, "move"}};
    wrapper->SaveGameWithMoves(user1, user2, "X", moves);
    wrapper->SaveGameWithMoves(user1, user2, "O", moves);
    wrapper->SaveGameWithMoves(user1, user2, "Tie", moves);
    
    auto stats = wrapper->GetHeadToHeadStats(user1, user2);
    EXPECT_EQ(get<0>(stats), 1); // user1 wins
    EXPECT_EQ(get<1>(stats), 1); // user2 wins
    EXPECT_EQ(get<2>(stats), 1); // ties
}

TEST_F(GameWrapperTest, HumanVsAIStats) {
    string user = CreateUniqueUser();
    wrapper->Register_Wrapper(user, "pass");
    
    vector<pair<int, string>> moves = {{1, "move"}};
    wrapper->SaveGameWithMoves(user, "AI", "X", moves);
    wrapper->SaveGameWithMoves(user, "AI", "O", moves);
    wrapper->SaveGameWithMoves(user, "AI", "Tie", moves);
    
    auto stats = wrapper->GetHumanVsAIStats(user);
    EXPECT_EQ(get<0>(stats), 1); // human wins
    EXPECT_EQ(get<1>(stats), 1); // AI wins
    EXPECT_EQ(get<2>(stats), 1); // ties
}

// Edge Cases
TEST_F(GameWrapperTest, EmptyBoardInitialization) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    auto board = wrapper->GetBoard();
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(board[i][j], ' ');
        }
    }
}

TEST_F(GameWrapperTest, PlayerSymbolAlternation) {
    wrapper->StartNewGame("P1", "P2", false, "", "X");
    EXPECT_EQ(wrapper->getCurrentUserSymbol(), 'X');
    
    wrapper->MakeHumanMove(1);
    EXPECT_EQ(wrapper->getCurrentUserSymbol(), 'O');
    
    wrapper->MakeHumanMove(2);
    EXPECT_EQ(wrapper->getCurrentUserSymbol(), 'X');
}
