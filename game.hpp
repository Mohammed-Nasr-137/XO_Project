#pragma once
#include <vector>
#include <string>
using namespace std;

class Game {
private:
    vector<vector<char>> board; // 3x3 board
    char currentPlayer;

public:
    Game();                                // constructor -> initializes everything
    void displayBoard() const;             // nb2a nzbt m3 el GUI
    bool makeMove(int row, int col);       // bya5od rakam el row w el column , w yshof valid wla la
    bool checkWin() const;                 // needs editing
    bool checkDraw() const;                // if all cells filled and no winner
    void switchPlayer(); 
    char getCurrentPlayer() const;         // Returns current player's symbol when we want to say it's his turn or he won
    char getCell(int row, int col) const;  // 
    void play(); 

    /////// lesa  ////////
    void check_char();
    void reset();
    void saveGame(const string& username);
    void loadGame(const string& username);


};
