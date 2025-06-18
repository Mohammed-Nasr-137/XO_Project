#include "user_system.h"
#include <openssl/sha.h>  // for SHA256
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>

UserSystem::UserSystem(const std::string& db_name) 
{
    if (openDatabase(db_name)) {
        createTables();
    } else {
        std::cerr << "Failed to open database.\n";
    }
}

UserSystem::~UserSystem() {
    closeDatabase();
}

bool UserSystem::openDatabase(const std::string& db_name) {
    return sqlite3_open(db_name.c_str(), &db) == SQLITE_OK;
}

void UserSystem::closeDatabase() {
    if (db) sqlite3_close(db);
}

void UserSystem::createTables() {
    char* errMsg = nullptr;

    const char* user_table_sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password_hash TEXT NOT NULL);";

    if (sqlite3_exec(db, user_table_sql, nullptr, nullptr, &errMsg)
        != SQLITE_OK) {
        std::cerr << "Error creating 'users' table: "
                  << errMsg << "\n";
        sqlite3_free(errMsg);
    }

    const char* history_table_sql =
        "CREATE TABLE IF NOT EXISTS game_history ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "player1 TEXT NOT NULL,"
        "player2 TEXT NOT NULL,"
        "winner TEXT NOT NULL);";

    if (sqlite3_exec(db, history_table_sql, nullptr, nullptr, &errMsg)
        != SQLITE_OK) {
        std::cerr << "Error creating 'game_history' table: "
                  << errMsg << "\n";
        sqlite3_free(errMsg);
    }

    const char* moves_table_sql =
        "CREATE TABLE IF NOT EXISTS game_moves ("
        "game_id INTEGER,"
        "move_index INTEGER,"
        "position INTEGER NOT NULL,"
        "comment TEXT,"
        "FOREIGN KEY (game_id) REFERENCES game_history(id));";

    if (sqlite3_exec(db, moves_table_sql, nullptr, nullptr, &errMsg)
        != SQLITE_OK) {
        std::cerr << "Error creating 'game_moves' table: "
                  << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}

bool UserSystem::registerUser(const std::string& username,
                             const std::string& password) {
    std::string hash = hashPassword(password);

    const char* sql =
        "INSERT INTO users (username, password_hash) VALUES (?, ?);";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr)
        != SQLITE_OK) return false;

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hash.c_str(), -1, SQLITE_STATIC);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);
    return success;
}

bool UserSystem::loginUser(const std::string& username,
                           const std::string& password) {
    std::string hash = hashPassword(password);

    const char* sql =
        "SELECT COUNT(*) FROM users WHERE username = ? AND password_hash = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr)
        != SQLITE_OK) return false;

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hash.c_str(), -1, SQLITE_STATIC);

    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_ROW &&
        sqlite3_column_int(stmt, 0) > 0) {
        success = true;
    }
    sqlite3_finalize(stmt);
    return success;
}

std::string UserSystem::hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password.c_str(), password.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(hash[i]);
    }
    return ss.str();
}

bool UserSystem::saveGameWithMoves(const std::string& player1,
                                   const std::string& player2,
                                   const std::string& winner,
                                   const std::vector<std::pair<int,
                                   std::string>>& moves) {
    sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    std::string winner_username;
    if (winner == "X") {
        winner_username = player1;
    } else if (winner == "O") {
        winner_username = player2;
    } else {
        winner_username = "Tie";
    }

    const char* insert_game_sql =
        "INSERT INTO game_history (player1, player2, winner) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt_game;

    if (sqlite3_prepare_v2(db, insert_game_sql, -1, &stmt_game, nullptr)
        != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt_game, 1, player1.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt_game, 2, player2.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt_game, 3, winner_username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt_game) != SQLITE_DONE) {
        sqlite3_finalize(stmt_game);
        return false;
    }

    int game_id = static_cast<int>(sqlite3_last_insert_rowid(db));
    sqlite3_finalize(stmt_game);

    const char* insert_move_sql =
        "INSERT INTO game_moves (game_id, move_index, position, comment) "
        "VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt_move;

    if (sqlite3_prepare_v2(db, insert_move_sql, -1, &stmt_move, nullptr)
        != SQLITE_OK) {
        return false;
    }

    for (size_t i = 0; i < moves.size(); ++i) {
        sqlite3_bind_int(stmt_move, 1, game_id);
        sqlite3_bind_int(stmt_move, 2, static_cast<int>(i));
        sqlite3_bind_int(stmt_move, 3, moves[i].first);

        if (!moves[i].second.empty()) {
            sqlite3_bind_text(stmt_move, 4, moves[i].second.c_str(), -1,
                              SQLITE_STATIC);
        } else {
            sqlite3_bind_null(stmt_move, 4);
        }

        if (sqlite3_step(stmt_move) != SQLITE_DONE) {
            sqlite3_finalize(stmt_move);
            return false;
        }
        sqlite3_reset(stmt_move);
    }

    sqlite3_finalize(stmt_move);
    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
    return true;
}

std::vector<std::tuple<int, std::string, std::string, std::string>>
UserSystem::getGameHistory(const std::string& username) {
    const char* sql =
        "SELECT id, player1, player2, winner "
        "FROM game_history "
        "WHERE player1 = ? OR player2 = ? "
        "ORDER BY id DESC;";

    sqlite3_stmt* stmt;
    std::vector<std::tuple<int, std::string, std::string, std::string>> history;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr)
        != SQLITE_OK) {
        return history;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string p1 =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string p2 =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string winner =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        history.emplace_back(id, p1, p2, winner);
    }

    sqlite3_finalize(stmt);
    return history;
}

std::vector<std::pair<int, std::string>>
UserSystem::loadGameMovesWithComments(int game_id) {
    const char* sql =
        "SELECT position, comment "
        "FROM game_moves "
        "WHERE game_id = ? "
        "ORDER BY move_index ASC;";

    sqlite3_stmt* stmt;
    std::vector<std::pair<int, std::string>> moves;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr)
        != SQLITE_OK) {
        return moves;
    }

    sqlite3_bind_int(stmt, 1, game_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int position = sqlite3_column_int(stmt, 0);
        const char* comment_text =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string comment;
        if (comment_text != nullptr) comment = std::string(comment_text);
        moves.emplace_back(position, comment);
    }

    sqlite3_finalize(stmt);
    return moves;
}

std::tuple<int, int, int>
UserSystem::getHeadToHeadStats(const std::string& user1,
                               const std::string& user2) {
    const char* sql =
        "SELECT player1, player2, winner "
        "FROM game_history "
        "WHERE (player1 = ? AND player2 = ?) OR "
        "(player1 = ? AND player2 = ?);";

    sqlite3_stmt* stmt;
    int user1Wins = 0, user2Wins = 0, ties = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr)
        != SQLITE_OK) {
        return std::make_tuple(0, 0, 0);
    }

    sqlite3_bind_text(stmt, 1, user1.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user2.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user2.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user1.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const std::string winner =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        if (winner == "Tie") {
            ++ties;
        } else if (winner == user1) {
            ++user1Wins;
        } else if (winner == user2) {
            ++user2Wins;
        }
    }

    sqlite3_finalize(stmt);
    return std::make_tuple(user1Wins, user2Wins, ties);
}

std::tuple<int, int, int>
UserSystem::getHumanVsAIStats(const std::string& humanUser) {
    const char* sql =
        "SELECT player1, player2, winner "
        "FROM game_history "
        "WHERE (player1 = ? AND player2 = 'AI') OR "
        "(player1 = 'AI' AND player2 = ?);";

    sqlite3_stmt* stmt;
    int humanWins = 0, aiWins = 0, ties = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr)
        != SQLITE_OK) {
        return std::make_tuple(0, 0, 0);
    }

    sqlite3_bind_text(stmt, 1, humanUser.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, humanUser.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const std::string winner =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        if (winner == "Tie") {
            ++ties;
        } else if (winner == humanUser) {
            ++humanWins;
        } else if (winner == "AI") {
            ++aiWins;
        }
    }
    sqlite3_finalize(stmt);
    return std::make_tuple(humanWins, aiWins, ties);
}
