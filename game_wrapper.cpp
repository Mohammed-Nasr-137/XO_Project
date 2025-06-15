// #include <iostream>
#include <vector>
#include <string>
// #include "ai.cpp"
#include "game_logic.cpp"
#include "user_system.cpp"

using namespace std;


class GameWrapper {
    private:
        UserSystem  sys_;
        AI          ai_;
        GameEngine  game_;
        bool        is_single_mode_;
        string      player1_;           // username1
        string      player2_;           // username2
        string      player1_symbol_;
        string      player2_symbol_;
        string      current_user_;      // used to tell gui whose move this is
        string      comment_;
        vector<pair<Move, string>> move_history_;

        vector<pair<int, string>> GetMoveHistory()
        {
            vector<pair<int, string>> moves;
            for (auto item : game_.get_moveHistory())
            {
                moves.push_back({item.first.position, item.second});
            }
            return moves;
        }

        void GetComment()
        {
            comment_ = ai_.audit_.GetLastExplanation();
        }

    public:
        GameWrapper() : sys_("game_db") {}

        bool Login_Wrapper(const string& username, const string& password)
        {   // is called when login button is clicked
            return sys_.loginUser(username, password);
        }

        bool Register_Wrapper(const string& username, const string& password)
        {   // is called when register button is clicked
            return sys_.registerUser(username, password);
        }

        void StartNewGame(const string& p1, const string& p2, bool is_single_mode, const string& ai_level, const string& chosen_symbol) 
        {
            // is called at the start of a new game whether it's single or multi (after signing in the 2nd user) or in case of reset button is clicked
            // called after a move is chosen
            // controls which player starts
            player1_ = p1;
            player2_ = p2;
            is_single_mode_ = is_single_mode;
            game_.Game_init();
            player1_symbol_ = chosen_symbol;
            player2_symbol_ = (chosen_symbol == "X") ? "O" : "X";
            current_user_ = (player1_symbol_ == "X") ? player1_ : player2_;
            if (is_single_mode) ai_.SetDifficulty(ai_level);
        }

        bool MakeHumanMove(int position) 
        {
            // used by every human player
            bool success = game_.makeMove(position, "Human move");
            if (success) 
            {
                current_user_ = (current_user_ == "X") ? "O" : "X";  // if move is made flip current user
            }
            return success;
        }

        bool MakeAIMove(int position) 
        {
            // used by ai if single mode
            pair<int, int> ai_move = ai_.GetBestMove(game_.get_board(), game_.getCurrentPlayer());
            bool success = game_.makeMove(position, comment_);
            if (success) 
            {
                current_user_ = (current_user_ == "X") ? "O" : "X";  // if move is made flip current user
            }
            return success; 
        }

        void Undo()
        {   // is called when undo button is clicked 
            if (is_single_mode_)
            {
                game_.undoMove();
                game_.undoMove();
            }
            else game_.undoMove();
        }

        pair<bool, string> CheckWinner()
        {
            // returns pair of (if winner, winner symbol)
            string current_winner_move = (current_user_ == "X") ? "O" : "X";  // checks the opposite move for a win
            string current_winner_user = "";
            bool is_win = game_.checkWin(current_winner_move);
            pair<bool, string> p = {is_win, current_winner_move};
            /*if (is_win)
            {
                current_winner_user = (current_winner_move == player1_symbol_) ? player1_ : player2_; // determine which user has won
            }*/
            return p;
        }

        bool CheckTie()
        {
            return game_.checkDraw();
        }

        vector<vector<char>> GetBoard()
        {
            return game_.get_board();
        }

        bool SaveGameWithMoves( 
            const string player1, // username1
            const string player2, // username2
            const string winner,  // winner symbol
            const vector<pair<int, string>> moves // pair of position and comment
        )
        {
            // used at the end of each game
            return sys_.saveGameWithMoves(player1, player2, winner, moves);
        }

        vector<tuple<int, string, string, string>> 
        GetGameHistory(const string username)
        {
            // given a username it returns a vector of tuples (game-id, player1, player2, winner(as a username))
            // used when gamehistory is clicked
            return sys_.getGameHistory(username);
        }

        vector<pair<int, string>>
        LoadGameMovesWithComments(int game_id)
        {
            // given an id (linked to the replay button in the list)
            // returns pair of position and comments 
            return sys_.loadGameMovesWithComments(game_id);
        }

        tuple<int, int ,int> GetHeadToHeadStats(const string user1, const string user2)
        {
            // given 2 users returns a tuple (wins1, wins2, ties)
            // used in the start of a multiplayer game
            return sys_.getHeadToHeadStats(user1, user2);
        }

        tuple<int, int ,int> GetHumanVsAIStats(const string humanUser)
        {
            // given a user returns a tuple (human-wins, ai-wins, ties)
            // used in the start of a singleplayer game
            return sys_.getHumanVsAIStats(humanUser);
        }
};



/* 


// init system and global variables
string game_winner;
// string difficulty = "";  // set by gui as "easy", "medium", "hard", and used by wrappers 
// UserSystem sys("game_db");
pair<string, string> cred_pair1, cred_pair2;



vector<pair<int, string>> get_moves(vector<pair<Move, string>> game_moves)
{
    vector<pair<int, string>> moves;
    for (auto item : game_moves)
    {
        moves.push_back({item.first.position, item.second});
    }
    return moves;
}

void game_flow(bool single, string diff = "")
{
    int user1_position;
    int user2_position;
    GameEngine game;

    if (single)  // if single init ai
    {
        AI ai_player;
        ai_player.SetDifficulty(diff);
    }

    game.Game_init();
    static char starter = 'X'; // is flipped when the game ends

    // cout << "\nEnter position (1-9), 0 to reset, 10 to undo: \n";
    
    while(!game.isGameOver())
    {
        game.displayBoard();
        
        
        if (game.getCurrentPlayer() == starter)
        {
            // cout << "\nPlayer " << game.getCurrentPlayer() << "'s turn.\nPosition (1-9): \n";
            cin >> user1_position;
        }
        else
        { 
            cout << "\nAI Player " << game.getCurrentPlayer() << "'s turn.\nPosition (1-9): \n";
            pair<int, int> ai_move = ai_player.GetBestMove(game.get_board(), game.getCurrentPlayer());
            user1_position = ai_move.first * 3 + ai_move.second +  1;
            cout << "\n" << ai_player.audit_.GetLastExplanation() << "\n";
        }

        
       

        // Resets the board 
        if(user1_position == 0)
        {
            game.Game_init();
            cout << "Board has been reset!\n";
            continue;
        }

        // undoes the move 
        else if(user1_position == 10)
        {
            game.undoMove();
            game.undoMove();
            continue; 
        }
        

        // variable that saves winner before switching turns 
        char current = game.getCurrentPlayer();

        game.makeMove(user1_position, ai_player.audit_.GetLastExplanation());

        // Check for win 
        if (game.checkWin(current))
        {
            game.displayBoard();
            cout << "Player " << current << " wins!\n";
            /*if (current == 'X')
            {
                game_winner = cred_pair.first;
            }
            else if (current == 'O')
            {
                game_winner = "AI";
            }
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
        starter = (starter == 'X') ? 'O' : 'X';
    }
    vector<pair<int, string>> moves = get_moves(game.get_moveHistory());
    // sys.saveGameWithMoves(cred_pair.first, "AI", game_winner, moves);   // here moves remains to be added
    
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



void display_gamemoves(vector<pair<int, string>> logged_moves)
{
    int move_number = 1;
    for (auto item : logged_moves)
    {
        cout << "move number: " << move_number << " , pos: " << item.first 
        << " , comment: " << item.second << "\n"; 
        move_number++;
    }
}

void display_history(vector<tuple<int, string, string, string>> logged_moves)
{
    for (auto item : logged_moves)
    {
        cout << "game id: " << get<0>(item) << " , player1: " << get<1>(item) 
        << " , player2: " << get<2>(item) << ", winner: " << get<3>(item) <<"\n"; 
    }
}






void single_player(const string difficulty)
{
    // is called after difficulty level is determined
    bool rematch = false;
    do
    {

        // game_flow(true, difficulty);
    } while (rematch);
    
}
*/


/* 
int main()
{
    // init sys
    
    bool success;
    
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
    
    
    
    tuple<int, int, int> stats = sys.getHumanVsAIStats(cred_pair.first);
    cout << "human: " << get<0>(stats) << ", ai: " << get<1>(stats) << ", ties: " << get<2>(stats) << "\n"; 
   

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

    // vector<pair<int, string>> logged_moves = sys.loadGameMovesWithComments(1);
    // display_gamemoves(logged_moves);
    vector<tuple<int, string, string, string>> history =  sys.getGameHistory("nasr");
    display_history(history);
    return 0;
}
*/
