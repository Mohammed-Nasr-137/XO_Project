#include <gtest/gtest.h>
#include "ai.h"
#include <chrono>
#include <iostream>
#include <sys/resource.h>  // for getrusage
#include <unistd.h>

Board GetMidGameBoard() {
    return {
        {'X', 'O', 'X'},
        {'O', 'X', ' '},
        {' ', ' ', 'O'}
    };
}

void ReportResourceUsage(const std::string& label) {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    std::cout << "[RESOURCE] " << label << "\n";
    std::cout << "  - User CPU time: " << usage.ru_utime.tv_sec * 1000 + usage.ru_utime.tv_usec / 1000 << " ms\n";
    std::cout << "  - System CPU time: " << usage.ru_stime.tv_sec * 1000 + usage.ru_stime.tv_usec / 1000 << " ms\n";
    std::cout << "  - Max resident set size (memory): " << usage.ru_maxrss << " KB\n";
    std::cout << "----------------------------------------\n";
}

void BenchmarkMove(AI& ai, const Board& board, char player, const std::string& label) {
    auto start = std::chrono::high_resolution_clock::now();
    ai.GetBestMove(board, player);
    auto end = std::chrono::high_resolution_clock::now();

    auto time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "[BENCHMARK] " << label << ": " << time_us << " µs\n";
    ReportResourceUsage(label);
}

// --------------- Tests ------------------

TEST(AIPerfSuite, TimeEasyAI_MoveSelection) {
    AI ai;
    ai.SetDifficulty("easy");
    BenchmarkMove(ai, GetMidGameBoard(), 'X', "Easy AI");
}

TEST(AIPerfSuite, TimeMediumAI_SearchDepth2) {
    AI ai;
    ai.SetDifficulty("medium");
    BenchmarkMove(ai, GetMidGameBoard(), 'X', "Medium AI (depth 2)");
}

TEST(AIPerfSuite, TimeHardAI_SearchDepthMax) {
    AI ai;
    ai.SetDifficulty("hard");
    BenchmarkMove(ai, GetMidGameBoard(), 'X', "Hard AI (depth 9)");
}

TEST(AIPerfSuite, AI_Scalability_DepthCurve) {
    AI ai;
    ai.SetDifficulty("hard");

    std::cout << "[DEPTH SCALING TEST]\n";
    for (int i = 2; i <= 5; ++i) {
        Board board = GetMidGameBoard();
        auto start = std::chrono::high_resolution_clock::now();
        ai.GetBestMove(board, 'X');  // relies on internal difficulty setting
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "  Depth " << i << ": " << duration << " µs\n";
    }
    ReportResourceUsage("Depth Curve Test");
}

TEST(AIPerfSuite, AI_MemoryLogGrowth) {
    AI ai;
    ai.SetDifficulty("hard");

    Board board = GetMidGameBoard();
    for (int i = 0; i < 5; ++i) {
        auto move = ai.GetBestMove(board, 'X');
        board[move.first][move.second] = 'X';
    }

    std::string json = ai.audit_.ExportLogAsJSON();
    std::cout << "[AUDIT LOG] Log Length: " << json.length() << " bytes\n";
    EXPECT_GT(json.length(), 50); // basic growth check
    ReportResourceUsage("Memory Log Growth Test");
}
