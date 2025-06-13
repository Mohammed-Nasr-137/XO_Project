#include <iostream>
#include <vector>
#include <string>
#include "ai.cpp"

using namespace std;


/* Implemented with the implmentation of undoMove() function */
struct Move
{
    int position;
    char player;
};

class GameEngine 
{
    private:
        /* defines a vector of vectors (board) like a 2D array or matrix where each element is a char for showing the game board */
        vector<vector<char>> board; 

        /* the variable that carries the character of the player in turn */
        char currentPlayer;

        /* defines a vector (moveHistory) for keeping track of all moves allowing undoing any move */
        // vector<Move> moveHistory;
        vector<pair<Move, string>> moveHistory;

        int playerValue(char cell)
        {
            /* converts the character stored in a board cell ('X', 'O', or ' ') into a numeric value */

            /* If the cell contains 'X', it returns 1. */
            if (cell == 'X') return 1;

            /* If the cell contains 'O', it returns -1. */
            if (cell == 'O') return -1;

            /* If the cell is empty (' ') or any other character, it returns 0 */
            return 0;
        }

    public:
        void Game_init()
        {
            /* Initializes the board */
            board = vector<vector<char>>(3, vector<char>(3, ' '));
            
            /* because X starts */
            currentPlayer = 'X';

            /* Clears the move history when the game is initialized or reset so you can’t undo moves from a previous game. */
            moveHistory.clear();
        }

    void displayBoard()
    {
        /* Gives the current state of the game continously */

        /*
        C++11 style
        for (const auto& x : y) means for each element x in container y
        auto lets the compiler figure out the type
        & means we are using a reference which is more efficient
        */
        for (const auto& row : board)
        {
            for (char cell : row)
            {
                /*
                Here we used a ternary operator
                is cell = space ? (if true put dot) : (if false put space)
                */
                cout << (cell == ' ' ? '.' : cell) << " ";
            }
            cout << endl;
        }
    }
    
    /* for updating the current player continously while changing turns */
    char getCurrentPlayer() const {   return currentPlayer;   }

    bool isValidMove(int position)
    {   
        /* Tests all the bad cases of moves placement*/

        /* we check first if the position is out of range , if out of range the function will return false and displays the board again with the last state before the invalid move */
        if(position < 1 || position > 9)
        {
            cout << "\nInvalid position! Choose 1-9.\n";
            return false;
        }

        /* These equations is to make the user interface easier by giving one input which is the desired position */
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;
        
        /* Second we check if the place is already taken */
        if(board[row][col] != ' ')
        {
            cout << "\nPosition " << position << " is already taken!\n";
            return false;
        }

        /* we reached here, which means that the if statements(bad cases) are not achieved then the move is valid */
        return true;
    }

    void makeMove(int position, string comment)
    {
        if(isValidMove(position))
        {  
            /* These equations is to make the user interface easier by giving one input which is the desired position */
            int row = (position - 1) / 3;
            int col = (position - 1) % 3;
            
            /* places the move */
            board[row][col] = currentPlayer;

            /* saves the state in case of undo */
            pair<Move, string> p = {{position, currentPlayer}, comment};
            moveHistory.push_back(p);

            /* changes turns */
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    void undoMove()
    {
        /* .empty() — returns true if the vector has no elements */
        if (moveHistory.empty())
        {
            /* if the player undoes the move at game initialization (No moves are made)*/
            cout << "No moves to be undone\n";
            return;
        }

        /* Get last move from history */
        /* .back() — returns a reference to the last element */
        pair<Move, string> lastMove = moveHistory.back();

        /* .pop_back() — removes the last element */
        moveHistory.pop_back();

        /* These equations is to make the user interface easier by giving one input which is the desired position */
        int row = (lastMove.first.position - 1) / 3;
        int col = (lastMove.first.position - 1) % 3;
        
        /* Revert the board */
        board[row][col] = ' ';
        
        /* Revert the player */ 
        currentPlayer = lastMove.first.player;
        cout << "Move has been undone!\n";
    }

    bool checkWin(char player) 
    {
        int row, col;

        /* The target sum for this player, where val is 1 for X and -1 for O */
        int val = (player == 'X') ? 1 : -1; 

        /* Check rows and columns */ 
        for (row = 0; row < 3; ++row)
        {
            int rowSum = 0, colSum = 0;
            for (col = 0; col < 3; ++col)
            {
                rowSum += playerValue(board[row][col]);
                colSum += playerValue(board[col][row]);
            }

            /* if the sum is 3 then it's win for X, if val=-3 then it's win for O */
            if (rowSum == 3 * val || colSum == 3 * val)
                return true;
        }

        /* Check diagonals */ 
        int diag1 = playerValue(board[0][0]) + playerValue(board[1][1]) + playerValue(board[2][2]);
        int diag2 = playerValue(board[0][2]) + playerValue(board[1][1]) + playerValue(board[2][0]);
        if (diag1 == 3 * val || diag2 == 3 * val)
            return true;

        /* if reached here then there is no win */
        return false;
    }

    /* as long as it doesn't find any empty cells and no win then it's good*/
    bool checkDraw()
    {
        for (const auto& row : board)
        {
            for (char cell : row)
            {
                if (cell == ' ')
                {
                    /* found an empty cell, not a draw */ 
                    return false; 
                }
            }
        }

        return true;
    }

    bool isGameOver()
    {
        /* Check if either player has won */ 
        if (checkWin('X') || checkWin('O'))
        {
            /* Game Over */
            return true;
        }

        /* Check for draw */ 
        if (checkDraw())
        {
            /* Game Over */
            return true;
        }

        /* Game is not over yet */
        return false;
    }

    Board get_board()
    {
        return board;
    }

    vector<pair<Move, string>> get_moveHistory()
    {
        return moveHistory;
    }

};