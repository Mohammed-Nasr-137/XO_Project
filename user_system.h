#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

#include <string>
#include <sqlite3.h>
#include <vector>

class UserSystem
{
public:
    UserSystem(const std::string& db_name);
    ~UserSystem();

    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);

    bool saveGameWithMoves(const std::string& player1,
                           const std::string& player2,
                           const std::string& winner,
                           const std::vector<std::pair<int, std::string>>& moves);

    std::vector<std::tuple<int, std::string, std::string, std::string>>
    getGameHistory(const std::string& username);

    std::vector<std::pair<int, std::string>>
    loadGameMovesWithComments(int game_id);

    std::tuple<int, int, int> getHeadToHeadStats(const std::string& user1, const std::string& user2);
    std::tuple<int, int, int> getHumanVsAIStats(const std::string& humanUser);


private:
    sqlite3* db;

    bool openDatabase(const std::string& db_name);



    void closeDatabase();
    void createTables();
    std::string hashPassword(const std::string& password);


};

#endif // USER_SYSTEM_H
