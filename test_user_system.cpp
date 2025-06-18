#include "gtest/gtest.h"
#include "user_system.h"
#include <cstdio>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
#include <climits>

class UserSystemTest : public ::testing::Test {
protected:
    std::string test_db = "test_user_system.db";
    UserSystem* userSystem;

    void SetUp() override {
        std::remove(test_db.c_str());
        userSystem = new UserSystem(test_db);
    }

    void TearDown() override {
        delete userSystem;
        std::remove(test_db.c_str());
    }
};

// ============================================================================
// CORE FUNCTIONALITY TESTS (8 tests)
// ============================================================================

// Test 1: Successful user registration
TEST_F(UserSystemTest, RegisterUserSuccess) {
    bool result = userSystem->registerUser("testuser", "password123");
    EXPECT_TRUE(result);
}

// Test 2: Duplicate username registration should fail
TEST_F(UserSystemTest, RegisterUserDuplicate) {
    userSystem->registerUser("testuser", "password123");
    bool result = userSystem->registerUser("testuser", "password123");
    EXPECT_FALSE(result);
}

// Test 3: Successful user login
TEST_F(UserSystemTest, LoginUserSuccess) {
    userSystem->registerUser("testuser", "password123");
    bool result = userSystem->loginUser("testuser", "password123");
    EXPECT_TRUE(result);
}

// Test 4: Login with wrong password should fail
TEST_F(UserSystemTest, LoginUserWrongPassword) {
    userSystem->registerUser("testuser", "password123");
    bool result = userSystem->loginUser("testuser", "wrongpassword");
    EXPECT_FALSE(result);
}

// Test 5: Save game and retrieve history
TEST_F(UserSystemTest, SaveGameAndRetrieveHistory) {
    std::vector<std::pair<int, std::string>> moves = {
        {0, "Opening move"},
        {4, "Center control"},
        {8, "Winning move"}
    };

    bool saveResult = userSystem->saveGameWithMoves("player1", "player2", "X", moves);
    EXPECT_TRUE(saveResult);

    auto history = userSystem->getGameHistory("player1");
    ASSERT_FALSE(history.empty());
    EXPECT_EQ(std::get<1>(history[0]), "player1");
    EXPECT_EQ(std::get<2>(history[0]), "player2");
    EXPECT_EQ(std::get<3>(history[0]), "player1"); // winner "X" maps to player1
}

// Test 6: Load game moves with comments
TEST_F(UserSystemTest, LoadGameMovesWithComments) {
    std::vector<std::pair<int, std::string>> moves = {
        {0, "First move"},
        {4, "Center control"},
        {8, ""}  // Empty comment
    };

    userSystem->saveGameWithMoves("player1", "player2", "X", moves);
    auto history = userSystem->getGameHistory("player1");
    ASSERT_FALSE(history.empty());

    int gameId = std::get<0>(history[0]);
    auto movesLoaded = userSystem->loadGameMovesWithComments(gameId);
    
    ASSERT_EQ(movesLoaded.size(), moves.size());
    for (size_t i = 0; i < moves.size(); ++i) {
        EXPECT_EQ(movesLoaded[i].first, moves[i].first);
        EXPECT_EQ(movesLoaded[i].second, moves[i].second);
    }
}

// Test 7: Head-to-head statistics
TEST_F(UserSystemTest, GetHeadToHeadStats) {
    std::vector<std::pair<int, std::string>> moves = {{0, ""}};

    // userA wins as X, userA wins as O, Tie game
    userSystem->saveGameWithMoves("userA", "userB", "X", moves);
    userSystem->saveGameWithMoves("userB", "userA", "O", moves);
    userSystem->saveGameWithMoves("userA", "userB", "Tie", moves);

    int userAWins, userBWins, ties;
    std::tie(userAWins, userBWins, ties) = userSystem->getHeadToHeadStats("userA", "userB");

    EXPECT_EQ(userAWins, 2);
    EXPECT_EQ(userBWins, 0);
    EXPECT_EQ(ties, 1);
}

// Test 8: Human vs AI statistics
TEST_F(UserSystemTest, GetHumanVsAIStats) {
    std::vector<std::pair<int, std::string>> moves = {{0, ""}};

    // Human wins, AI wins, Tie game
    userSystem->saveGameWithMoves("human", "AI", "X", moves);
    userSystem->saveGameWithMoves("AI", "human", "X", moves);
    userSystem->saveGameWithMoves("human", "AI", "Tie", moves);

    int humanWins, aiWins, ties;
    std::tie(humanWins, aiWins, ties) = userSystem->getHumanVsAIStats("human");

    EXPECT_EQ(humanWins, 1);
    EXPECT_EQ(aiWins, 1);
    EXPECT_EQ(ties, 1);
}

// ============================================================================
// EDGE CASES AND VALIDATION TESTS (6 tests)
// ============================================================================

// Test 10: Login nonexistent user should fail
TEST_F(UserSystemTest, LoginUserNonexistent) {
    bool result = userSystem->loginUser("nonexistent", "password123");
    EXPECT_FALSE(result);
}

// Test 11: Game history for nonexistent user should be empty
TEST_F(UserSystemTest, GetHistoryForNonexistentUser) {
    auto history = userSystem->getGameHistory("nonexistent");
    EXPECT_TRUE(history.empty());
}

// Test 12: Load moves for nonexistent game should be empty
TEST_F(UserSystemTest, LoadMovesForNonexistentGame) {
    auto moves = userSystem->loadGameMovesWithComments(999);
    EXPECT_TRUE(moves.empty());
}

// Test 13: Head-to-head stats with no games should return zeros
TEST_F(UserSystemTest, HeadToHeadStatsNoGames) {
    int user1Wins, user2Wins, ties;
    std::tie(user1Wins, user2Wins, ties) = userSystem->getHeadToHeadStats("user1", "user2");
    
    EXPECT_EQ(user1Wins, 0);
    EXPECT_EQ(user2Wins, 0);
    EXPECT_EQ(ties, 0);
}

// Test 14: Save game with tie result
TEST_F(UserSystemTest, SaveGameWithTieResult) {
    std::vector<std::pair<int, std::string>> moves = {{0, ""}, {1, ""}, {2, ""}};

    bool saveResult = userSystem->saveGameWithMoves("player1", "player2", "Tie", moves);
    EXPECT_TRUE(saveResult);

    auto history = userSystem->getGameHistory("player1");
    ASSERT_FALSE(history.empty());
    EXPECT_EQ(std::get<3>(history[0]), "Tie");
}

// ============================================================================
// SECURITY AND ROBUSTNESS TESTS (3 tests)
// ============================================================================

// Test 15: SQL injection prevention
TEST_F(UserSystemTest, SQLInjectionPrevention) {
    std::string maliciousInput = "'; DROP TABLE users; --";
    
    // System should handle malicious input gracefully without crashing
    EXPECT_NO_FATAL_FAILURE({
        userSystem->registerUser(maliciousInput, "password");
        userSystem->loginUser(maliciousInput, "password");
        userSystem->getGameHistory(maliciousInput);
    });
}

// Test 16: Unicode character handling
TEST_F(UserSystemTest, UnicodeCharacterHandling) {
    std::string unicodeUsername = "用户名";
    
    bool result = userSystem->registerUser(unicodeUsername, "password123");
    if (result) {
        EXPECT_TRUE(userSystem->loginUser(unicodeUsername, "password123"));
        
        std::vector<std::pair<int, std::string>> moves = {{0, "test"}};
        EXPECT_TRUE(userSystem->saveGameWithMoves(unicodeUsername, "opponent", "X", moves));
    }
}

// Test 17: Boundary values for game positions
TEST_F(UserSystemTest, GamePositionBoundaryValues) {
    std::vector<std::pair<int, std::string>> boundaryMoves = {
        {0, "Minimum valid position"},
        {8, "Maximum valid position"},
        {-1, "Below minimum"},
        {9, "Above maximum"}
    };
    
    bool result = userSystem->saveGameWithMoves("player1", "player2", "X", boundaryMoves);
    EXPECT_TRUE(result); // Current implementation doesn't validate positions
    
    auto history = userSystem->getGameHistory("player1");
    ASSERT_FALSE(history.empty());
    
    int gameId = std::get<0>(history[0]);
    auto loadedMoves = userSystem->loadGameMovesWithComments(gameId);
    EXPECT_EQ(loadedMoves.size(), boundaryMoves.size());
}

// ============================================================================
// PERFORMANCE AND CONCURRENCY TESTS (3 tests)
// ============================================================================

// Test 18: Concurrent user registration
TEST_F(UserSystemTest, ConcurrentUserRegistration) {
    std::vector<std::thread> threads;
    std::vector<bool> results(5);
    
    // Simulate multiple threads trying to register the same username
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([this, &results, i]() {
            results[i] = userSystem->registerUser("concurrent_user", "password");
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Only one registration should succeed due to UNIQUE constraint
    int successCount = std::count(results.begin(), results.end(), true);
    EXPECT_EQ(successCount, 1);
}

// Test 19: Large dataset handling
TEST_F(UserSystemTest, LargeDatasetHandling) {
    const int NUM_USERS = 50;
    const int GAMES_PER_USER = 3;
    
    // Register many users
    for (int i = 0; i < NUM_USERS; ++i) {
        std::string username = "user" + std::to_string(i);
        EXPECT_TRUE(userSystem->registerUser(username, "password"));
    }
    
    // Create many games
    std::vector<std::pair<int, std::string>> moves = {{0, "move1"}, {1, "move2"}};
    for (int i = 0; i < NUM_USERS; i += 2) {
        for (int j = 0; j < GAMES_PER_USER; ++j) {
            std::string player1 = "user" + std::to_string(i);
            std::string player2 = "user" + std::to_string(i + 1);
            EXPECT_TRUE(userSystem->saveGameWithMoves(player1, player2, "X", moves));
        }
    }
    
    // Verify data retrieval
    auto history = userSystem->getGameHistory("user0");
    EXPECT_EQ(history.size(), GAMES_PER_USER);
}

// Test 20: Complex statistics scenario
TEST_F(UserSystemTest, ComplexStatisticsScenario) {
    std::vector<std::pair<int, std::string>> moves = {{0, ""}};
    
    // Create complex game history for both head-to-head and AI stats
    userSystem->saveGameWithMoves("playerA", "playerB", "X", moves); // A wins
    userSystem->saveGameWithMoves("playerB", "playerA", "X", moves); // B wins
    userSystem->saveGameWithMoves("playerA", "playerB", "Tie", moves);     // Tie
    userSystem->saveGameWithMoves("playerA", "AI", "X", moves);      // A beats AI
    userSystem->saveGameWithMoves("AI", "playerA", "X", moves);           // AI beats A
    
    // Test head-to-head stats
    int aWins, bWins, ties;
    std::tie(aWins, bWins, ties) = userSystem->getHeadToHeadStats("playerA", "playerB");
    EXPECT_EQ(aWins, 1);
    EXPECT_EQ(bWins, 1);
    EXPECT_EQ(ties, 1);
    
    // Test AI stats
    int humanWins, aiWins, aiTies;
    std::tie(humanWins, aiWins, aiTies) = userSystem->getHumanVsAIStats("playerA");
    EXPECT_EQ(humanWins, 1);
    EXPECT_EQ(aiWins, 1);
    EXPECT_EQ(aiTies, 0);
}
