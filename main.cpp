#include <iostream>
#include <vector>
#include <string>
// #include "ai.cpp"
#include "game_logic.cpp"
#include "user_system.cpp"

using namespace std;


void game_flow()
{
    int position;
    int ai_position;
    GameEngine game;

    AI ai_player;
    string diff = "easy";

    ai_player.SetDifficulty(diff);

    cout << "\nEnter position (1-9), 0 to reset, 10 to undo: \n";
    game.Game_init();
    while(!game.isGameOver())
    {
        game.displayBoard();
        
        
        if (game.getCurrentPlayer() == 'X')
        {
            cout << "\nPlayer " << game.getCurrentPlayer() << "'s turn.\nPosition (1-9): \n";
            cin >> position;
        }
        else
        { 
            cout << "\nAI Player " << game.getCurrentPlayer() << "'s turn.\nPosition (1-9): \n";
            pair<int, int> ai_move = ai_player.GetBestMove(game.get_board(), game.getCurrentPlayer());
            position = ai_move.first * 3 + ai_move.second +  1;
            cout << "\n" << ai_player.audit_.GetLastExplanation() << "\n";
        }

        
       

        // Resets the board 
        if(position == 0)
        {
            game.Game_init();
            cout << "Board has been reset!\n";
            continue;
        }

        // undoes the move 
        else if(position == 10)
        {
            game.undoMove();
            continue; 
        }
        

        // variable that saves winner before switching turns 
        char current = game.getCurrentPlayer();

        game.makeMove(position);

        // Check for win 
        if (game.checkWin(current))
        {
            game.displayBoard();
            cout << "Player " << current << " wins!\n";
            break;
        }

        // Check for draw 
        if (game.checkDraw())
        {
            game.displayBoard();
            cout << "It's a draw!\n";
            break;
        }
 

    }
}


int main()
{
    // init sys
    UserSystem sys("game_db");
    string name, password;

    cout << "Hello to XO world \n";
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your pass: ";
    cin >> password;
    sys.registerUser(name, password);

    // start game
    game_flow();

    int choice;
    cout << "what do you want to do? (1:replay, 2:exit)  ";
    cin >> choice;

    while (choice == 1)
    {
        game_flow();
        cout << "what do you want to do? (1:replay, 2:exit)  ";
        cin >> choice;
    }

    
    return 0;
}



/*
int main()
{ 
    int position;
    int ai_position;
    GameEngine game;

    AI ai_player;
    string diff = "hard";

    ai_player.SetDifficulty(diff);

    cout << "\nEnter position (1-9), 0 to reset, 10 to undo: \n";
    game.Game_init();
    while(!game.isGameOver())
    {
        game.displayBoard();
        
        
        if (game.getCurrentPlayer() == 'X')
        {
            cout << "\nPlayer " << game.getCurrentPlayer() << "'s turn.\nPosition (1-9): \n";
            cin >> position;
        }
        else
        { 
            cout << "\nAI Player " << game.getCurrentPlayer() << "'s turn.\nPosition (1-9): \n";
            pair<int, int> ai_move = ai_player.GetBestMove(game.get_board(), game.getCurrentPlayer());
            position = ai_move.first * 3 + ai_move.second +  1;
            cout << "\n" << ai_player.audit_.GetLastExplanation() << "\n";
        }

        
       

        // Resets the board 
        if(position == 0)
        {
            game.Game_init();
            cout << "Board has been reset!\n";
            continue;
        }

        // undoes the move 
        else if(position == 10)
        {
            game.undoMove();
            continue; 
        }
        

        // variable that saves winner before switching turns 
        char current = game.getCurrentPlayer();

        game.makeMove(position);

        // Check for win 
        if (game.checkWin(current))
        {
            game.displayBoard();
            cout << "Player " << current << " wins!\n";
            break;
        }

        // Check for draw 
        if (game.checkDraw())
        {
            game.displayBoard();
            cout << "It's a draw!\n";
            break;
        }
 

    }
    return 0;
}

*/
