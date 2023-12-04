#include <iostream>
#include <string>
#include "ChessBoard.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Piece.h"
#include "Observer.h"
#include "Level.h"

using namespace std;


// Helper Function to convert a char to an int
int convertToInt(char c) {
    if(c >= 'a' && c <= 'h') {
        return (c - 'a'); // 'a' is equal to 97
        // We use 0-7
    } else {
        return -1; // Returns false if it is not a valid letter on the board
    }
}

// Determines if the inputted string is a valid player
bool validPlayer(const string& player) {
    if (player == "human") return true;
    if (player.length() == 11 && player.substr(0, 8) == "computer") {
        int level = player[9] - '0';  // Convert character to integer
        return level >= 1 && level <= 4;
    }
    return false;
}


void outputRules() {
    string art =
    "+----------------------------------------------------+\n"
    "|                                                    |\n"
    "|                    Chess Game                      |\n"
    "|                   _                                |\n"
    "|                  | |                               |\n"
    "|               ___| |__   ___  ___ ___              |\n"
    "|              / __| '_ \\ / _ \\/ __/ __|             |\n"
    "|             | (__| | | |  __/\\__ \\__ \\             |\n"
    "|              \\___|_| |_|\\___||___/___/             |\n"
    "|                                                    |\n"
    "|          By: Chiara, Franklin, Helena              |\n"
    "|                                                    |\n"
    "+----------------------------------------------------+\n";
    cout << art << endl;
    cout << "Welcome to our chess game. Please follow the rules and commands strictly.\n";
    cout << "Commands:\n";
    cout << "  - game white-player black-player: Starts a new game. 'white-player' and 'black-player' can be 'human' or 'computer[1-4]'.\n";
    cout << "  - resign: Concede the game to your opponent.\n";
    cout << "  - move <start> <end>: Make a move from <start> to <end>. For castling, use king's initial and final positions.\n";
    cout << "  - move <start> <end> <promotion>: Pawn promotion move.\n";
    cout << "  - move: Computer player will make a move.\n\n";
    cout << "  - skip: Skip the current turn.\n\n";

    cout << "Setup Commands (only available when a game is not running):\n";
    cout << "  - setup: Enter setup mode.\n";
    cout << "  - + <char> <coords>: Add piece at the specified coordinates.\n";
    cout << "  - - <coords>: Remove piece at the specified coordinates.\n";
    cout << "  - = <colour>: Set the next turn to the specified colour.\n";
    cout << "  - done: Exit setup mode, if all setup conditions are met.\n\n";

    cout << "In setup mode, ensure the following conditions are met before exiting:\n";
    cout << "  - One white king and one black king must be on the board.\n";
    cout << "  - No pawns are on the first or last rows of the board.\n";
    cout << "  - Neither king is in check.\n\n";

    cout << "To get started with a match, enter game for a default board or setup for a custom one." << endl;
}


int main() {
    string cmd;
    bool usedSetup = false;
    shared_ptr<ChessBoard> cb = make_shared<ChessBoard>();

    outputRules();

    while (cin >> cmd) {
        // Make a prompt output to get enter game or setup
        // We prompt the user to enter game or setup
        // If they enter game, they immediately start a game. THey are prompted for player 1 and player 2
        // After that, we check whether they inputted setup before this (inputting setup before this meant they setup a custom board). If false
        // use the default board. If true, that means they used setup beforehand so we use that custome board.
        // If we are to use the default board, we simply default construct that gameboard and get players
        // If we we are to use the custom board, we just get players cuz we already created this custom board in setup.
        // On top of this, we have a isEnd that resets the gameBoard and players.
        shared_ptr<Player> playerWhite;
        shared_ptr<Player> playerBlack;

        // If the user chooses to start a match 
        if(cmd == "game") {
            string player1, player2;
            int level, level2;
            
            // While loop to handle input from the user for player 1 and player 2
            while (cin >> player1 >> player2) {
                if (!(validPlayer(player1) && validPlayer(player2))) { // If Invalid players
                    cout << "Invalid Input. Please read the rules again. " << endl;
                    cout << "  - game white-player black-player: Starts a new game. 'white-player' and 'black-player' can be 'human' or 'computer[1-4]'" << endl;
                    // Prompt the user to start from the beginning and input game player1 player2 again
                    cin >> cmd;
                    continue;
                } else if (player1 == "human" && player2 == "human") { //If both Humans

                    // set boths players to Human instances
                    playerWhite = make_shared<Human>(1, cb);
                    playerBlack = make_shared<Human>(0, cb);
                    cb->setupPlayers(playerWhite, playerBlack); // Setup the Observers of chessboard as playerWhite and playerBlack
                    break; 

                } else if (player1 == "human" && player2.substr(0,8) == "computer" ) { // If human and computer

                    try { //Try catch block to handle if the user inputted an incorrect number or invalid input
                        level2 = stoi(player2.substr(9, 1));
                        if (!(level2 >= 1 && level2 <= 4))  {
                            throw invalid_argument("Invalid Level");
                        }
                    } catch (...) {
                        cout << "Invalid input. Please enter a valid level." << endl;
                        continue;
                    }
                    
                    level2 = stoi(player2.substr(9, 1));
                    // continue the if statement and reach the invalid input
                    playerWhite = make_shared<Human>(1, cb);
                    playerBlack = make_shared<Computer>(0, cb, level2);
                    // Create a human and computer player based on the level
                    // Both take in a ChessBoard Observer (ChessBoard is a Subclass)
                    cb->setupPlayers(playerWhite, playerBlack);
                    break;

                } else if (player1.substr(0,8) == "computer" && player2 == "human" ) {

                    try {
                        level = stoi(player1.substr(9, 1));
                        if (!(level >= 1 && level <= 4))  {
                            throw invalid_argument("Invalid Level");
                        }
                    } catch (...) {
                        cout << "Invalid input. Please enter a valid level." << endl;
                        continue;
                    }

                    level = stoi(player1.substr(9, 1));
                    playerWhite = make_shared<Computer>(1, cb, level);
                    playerBlack = make_shared<Human>(0, cb);
                    cb->setupPlayers(playerWhite, playerBlack); // Then players
                    break;

                } else if (player1.substr(0,8) == "computer" && player2.substr(0,8) == "computer" ) {

                    try {
                        level = stoi(player1.substr(9, 1)); 
                        level2 = stoi(player2.substr(9, 1));
                        if (!(level >= 1 && level <= 4 && level2 >= 1 && level2 <=4))  {
                            throw invalid_argument("Invalid Level");
                        }
                    } catch (...) {
                        cout << "Invalid input. Please enter a valid level." << endl;
                        continue;
                    }

                    level = stoi(player1.substr(9, 1)); 
                    level2 = stoi(player2.substr(9, 1));

                    playerWhite = make_shared<Computer>(1, cb, level);
                    playerBlack = make_shared<Computer>(0, cb, level2);
                    cb->setupPlayers(playerWhite, playerBlack); // Then players
                    break;

                } else { // Else Case
                    cout << "Invalid Input. Please read the rules again. " << endl;
                    cout << "  - game white-player black-player: Starts a new game. 'white-player' and 'black-player' can be 'human' or 'computer[1-4]'" << endl;
                    cin >> cmd;
                }
            }

            // If the user did not use setup, we setup a default board
            if(!usedSetup) cb->defaultBoard(); 
            else cb->setUpStartMoves(); // Else, we set up the starting moves of the custom board

            string cmd2;
            cout << *(cb); // Output the chessboard

            while(cin >> cmd2) {
                if(!cb->getTurn()) { // In our constructor, turn is opposite of piece colours. Turn = true -> Black's turn
                    if (cmd2 == "move" && player1 == "human") {

                        string start, end;
                        cin >> start >> end;

                        try { //Try catch block to handle conversion of inputted letter and number coordinates to valid Vec coordinate
                            int y = stoi(start.substr(1));
                            int x = convertToInt(start.substr(0,1)[0]);
                            int x2 = convertToInt(end.substr(0,1)[0]);
                            int y2 = stoi(end.substr(1));
                            // If the coordinates are out of bounds, throw an exception
                            if (!(x >= 0 && x <= 7 && y >= 1 && y <= 8 && x2 >= 0 && x2 <= 7 && y2 >= 1 && y2 <= 8)) {
                                throw invalid_argument("Invalid coordinates");
                            }
                        } catch (...) { // Enter catch block to handle exceptions
                            cout << "Invalid input. Please enter valid coordinates." << endl;
                            continue;
                        }

                        // Proper Conversion
                        int x = convertToInt(start.substr(0,1)[0]);
                        int y = stoi(start.substr(1));
                        Vec coordinate1 = Vec{x, y - 1};

                        int x2 = convertToInt(end.substr(0,1)[0]);
                        int y2 = stoi(end.substr(1));
                        Vec coordinate2 = Vec{x2, y2 - 1};
                        // Dynamically cast the Observer Players from chessboard into Human or Computer based on what was inputted by the user
                        shared_ptr<Human> humanWhite = dynamic_pointer_cast<Human>(cb->getPlayerWhite());
                        if(humanWhite->makeHumanMove(coordinate1, coordinate2)) { // Returns if it was a valid move
                            // Valid Move
                            if(cb->upgradePawn(coordinate2)) { // If a Pawn was moved to the end of the board 
                                char newPiece;
                                cout << "Please input the character you want the Pawn to be upgraded to : " << endl;
                                while (cin >> newPiece) {
                                    if (!((newPiece == 'Q') || (newPiece == 'R')  || (newPiece == 'N')  || (newPiece == 'B'))){ cout << "Invalid Input. Try Again!"  << endl; continue;}
                                    cb->setupWithChar(newPiece, coordinate2); // Handle invalid input
                                    break;
                                }
                            } else cin.ignore(80, '\n'); // Ignore extra characters if the user incorrectly thought the move they made was an upgrade move

                        } else {

                            cout << "Invalid move. Please retry" << endl;

                        }
                    } else if(cmd2 == "move" && player1.substr(0,8) == "computer") { // If player1 is a computer
                        // Make Computer Move
                        // Dynamically Cast the Observers playerWhite to a Computer to have access to Computer Class functions
                        shared_ptr<Computer>  computerWhite = dynamic_pointer_cast<Computer>(cb->getPlayerWhite());
                        Vec end = computerWhite->makeComputerMove(); // Returns the end coordinate of the move
                        if(cb->upgradePawn(end)){ // If the random move made upgraded a Pawn, automatically convert it to a Queen
                            cb->setupWithChar('Q', end);
                        }

                    } else if(cmd2 == "resign") { // If the player chooses to resign
                        //Player1 now has to lose
                        cb->forfeit(); // This function will update the white and black score
                        cout << *(cb); // Output the chessboard

                        // Restart the Match. Sets values and fields back to their default values
                        cb->restartGame(); // Restart match
                        break;

                    } else if (cmd2 == "skip") { // Skip the current turn

                        cb->setTurn(!cb->getTurn());

                    } else {

                        cout << "Invalid Command. Try again" << endl;

                    }
                } else { // Same if statements but for player2
                    if (cmd2 == "move" && player2 == "human") {
                        string start, end;
                        cin >> start >> end;

                        try {
                            int y = stoi(start.substr(1));
                            int x = convertToInt(start.substr(0,1)[0]);

                            int x2 = convertToInt(end.substr(0,1)[0]);
                            int y2 = stoi(end.substr(1));

                            if (!(x >= 0 && x <= 7 && y >= 1 && y <= 8 && x2 >= 0 && x2 <= 7 && y2 >= 1 && y2 <= 8)) {
                                throw invalid_argument("Invalid coordinates");
                            }
                        } catch (...) {
                            cout << "Invalid input. Please enter valid coordinates." << endl;
                            continue;
                        }

                        int x = convertToInt(start.substr(0,1)[0]);
                        int y = stoi(start.substr(1));
                        Vec coordinate1 = Vec{x, y - 1};

                        int x2 = convertToInt(end.substr(0,1)[0]);
                        int y2 = stoi(end.substr(1));

                        Vec coordinate2 = Vec{x2, y2 - 1}; // Start at row 0

                        shared_ptr<Human> humanBlack = dynamic_pointer_cast<Human>(cb->getPlayerBlack());

                        if(humanBlack->makeHumanMove(coordinate1, coordinate2)) {

                            if(cb->upgradePawn(coordinate2)) {
                                char newPiece;
                                cout << "Please input the character you want the Pawn to be upgraded to : " << endl;
                                while (cin >> newPiece) {
                                    if (!((newPiece == 'q') || (newPiece == 'r')  || (newPiece == 'n')  || (newPiece == 'n'))) { cout << "Invalid Input. Try Again!"  << endl; continue;}
                                    cb->setupWithChar(newPiece, coordinate2);
                                }
                            } else cin.ignore(80, '\n');


                        } else {

                            cout << "Invalid move. Please retry" << endl;

                        }

                    } else if (cmd2 == "move" && player2.substr(0,8) == "computer") {

                        shared_ptr<Computer> computerBlack = dynamic_pointer_cast<Computer>(cb->getPlayerBlack());

                        Vec end = computerBlack->makeComputerMove();
                        if(cb->upgradePawn(end)){
                            cb->setupWithChar('q', end);
                        }

                    } else if(cmd2 == "resign") {
                        // Player2 has to lose
                        cb->forfeit();
                        cout << *(cb);
                        cb->restartGame();
                        break;

                    } else if (cmd2 == "skip") {

                        cb->setTurn(!cb->getTurn());

                    } else {

                        cout << "Invalid Command. Try again" << endl;

                    }
                }
                cout << *(cb);
            }
        } else if (cmd == "setup") { // If the user chooses to enter setup mode
            cout << "Entered Setup Mode : " << endl; 
            string cmd2, coord, colour;
            char piece;
            
            // Set the default turn as White goes first with the option to change by the user
            cb->setupTurn(false); 

            while(cin >> cmd2) {

                if(cmd2 == "+") { // Add function

                    cin >> piece >> coord;

                    try {
                        // Checks if it is a valid coordinate
                        int x = convertToInt(coord.substr(0,1)[0]);
                        int y = stoi(coord.substr(1));

                        if ((!(x >=0 && x <=7) || !(y <= 8 && y >= 1)) || !(piece == 'k' || piece == 'K' || piece == 'q' || piece == 'Q' ||
                            piece == 'b' || piece == 'B' || piece == 'n' || piece == 'N' ||
                            piece == 'r' || piece == 'R' || piece == 'p' || piece == 'P')) { // CHecks if the user inputted a valid piece and coordinate
                            throw invalid_argument("Invalid Piece/Coordinate");
                        }
                    } catch (...) {
                        cout << "Invalid input. Please enter valid coordinates." << endl;
                        continue;
                    }

                    int x = convertToInt(coord.substr(0,1)[0]);
                    int y = stoi(coord.substr(1));
                    Vec coordinate = Vec{x, y- 1};
                        
                    // If any of the added pieces are kings, set the White and Black King coordinates of the chessboard
                    if(piece == 'k') cb->setBlackKing(coordinate); 
                    if(piece == 'K') cb->setWhiteKing(coordinate);
                    cb->setupWithChar(piece, coordinate); // Setup the board with the inputted piece at the coordinate
                    cout << *(cb);
   
                } else if (cmd2 == "-") { //Remove the piece at the coordinate

                    cin >> coord;

                    try {
                        int x = convertToInt(coord.substr(0,1)[0]);
                        int y = stoi(coord.substr(1));

                         if ((!(x >=0 && x <=7) || !(y <= 8 && y >= 1))) {
                            throw invalid_argument("Invalid coordinates");
                        }
                    } catch (...) {
                        cout << "Invalid input. Please enter valid coordinates." << endl;
                        continue;
                    }

                    int x = convertToInt(coord.substr(0,1)[0]);
                    int y = stoi(coord.substr(1));
                    Vec coordinate = Vec{x, y - 1}; // We have to minus one because we are 0-7

                    cb->setupWithChar(cb->getEmptyPiece(coordinate)->getType(), coordinate); // Sets up that coordinate with the corresponding empty piece
                    cout << *(cb);

                } else if (cmd2 == "=") { // Sets the turn when the game starts
                    
                    if (cin >> colour) {

                        if(colour == "black") {
                            cb->setupTurn(1); // Setup whose turn will go first once the game has started
                        } else if (colour == "white") {
                            cb->setupTurn(0);
                        } else {
                            cout << "Invalid input, please try again." << endl;
                        }
                        cout << *(cb);
                    } else { cout << "Invalid input, please try again." << endl;}

                } else if (cmd2 == "done") { // User is done setting up

                    if(cb->boardIsValid()) { // Checks if the board is valid
                        usedSetup = true;
                        break; // Only case where we break
                        // Now a flag has been raised telling the main that the game has been setup with a gameboard.
                    }
                    cout << "Invalid Board Setup" << endl;
                    cb->restartGame();
                    break;

                } else {

                    cout << "Invalid Input, try Again" << endl;

                }

            }
        } else { // Invalid Input

            cout << "Invalid Input, try Again" << endl;

        }
        if(!cin.eof()) cout << "To get started with a match, enter game or setup." << endl;
    }
    // END OF GAME
    cb->setDisplayScore(true);
    cout << endl;
    cout << "Thank you for playing. We hope you enjoyed!" << endl;
    cout << "Make sure to play again!" << endl;
    return 0;
}

