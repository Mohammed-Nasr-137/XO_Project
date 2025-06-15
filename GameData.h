#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QString>

class GameData {
public:
    static GameData& instance() {
        static GameData _instance;
        return _instance;
    }

    QString firstPlayer;
    QString secondPlayer;
    QString P1turn;
    QString Anotherturn;
    QString mode ="";
    QString level ="";
    bool tracker = true ;
     bool box_1 =false;
    bool box_2=false;

private:
    GameData() {} // private constructor (singleton pattern)
};
#endif // GAMEDATA_H
