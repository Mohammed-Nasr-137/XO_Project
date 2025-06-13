#include <iostream>
#include <vector>
#include <string>
// #include "ai.cpp"
#include "game_logic.cpp"
#include "user_system.cpp"

using namespace std;

string game_winner;


void game_flow()
{
    int position;
    int ai_position;
    GameEngine game;

    AI ai_player;
    string diff = "medium";

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
            game_winner = current;
            break;
        }

        // Check for draw 
        if (game.checkDraw())
        {
            game.displayBoard();
            cout << "It's a draw!\n";
            game_winner = "Tie";
            break;
        }
 

    }
}

pair<string, string> get_name_and_pass()
{
    string name, password;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your pass: ";
    cin >> password;
    return make_pair(name, password);
} 


int main()
{
    // init sys
    UserSystem sys("game_db");
    bool success;
    pair<string, string> cred_pair;
    do
    {
        int acc;
        cout << "Hello to XO world \nRegister or login (1,2): ";
        cin >> acc;
        cred_pair = get_name_and_pass();
        success = false;
    if (acc == 1) 
    {
        success = sys.registerUser(cred_pair.first, cred_pair.second);
        if (!success) cout << "reg failed or user already exits! \n";
    }
    else if (acc == 2)
    {
        success = sys.loginUser(cred_pair.first, cred_pair.second);
        if (!success) cout << "login failed! \n";
    }
    } while (!success);
    
    
    
   

    // start game
    game_flow();

    // sys.saveGameWithMoves(cred_pair.first, "AI", game_winner, );   // here moves remains to be added
    
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
