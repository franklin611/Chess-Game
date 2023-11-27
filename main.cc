#include <iostream>
#include <string>
#include "ChessBoard.h"
#include "Player.h"
#include "Game.h"
#include "Piece.h"

using namespace std;


int convertToInt(char c) {
    if(c >= 'a' && c <= 'h') {
        return c - 'a' + 1;
        // Just going to make a decision that we use 1-8 not 0-7
    } else {
        return -1;
    }
}

void outputRules() {
    string art =
    "+----------------------------------------------------+\n"
    "|                                                    |\n"
    "|                    Chess Game                      |\n"
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

    cout << "Please input your commands:\n";
}


int main() {
    string cmd;
    // Xwindow xw;
    Game game = Game{};
    bool usedSetup = false;
    ChessBoard cb = ChessBoard{};
    // Creates a default empty gameBoard. With just empty pieces 
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

         
        if(cmd == "game") {
            // Once the user has entered game, they should not be able to exit the below while loop until the game is over. 
            //To setup a new game, we take two input playerWhite playerBlack.
            String player1, player2;
            cin >> player1 >> player2;

            unique_ptr<Player> playerWhite, playerBlack;

            if(player1 == "human") {
                playerWhite = make_unique<Human>(1)
            } else {
                int level = stoi(player1.substr(9));
                playerWhite = make_unique<Computer>(1, level);
            }
            if(player2 == "human") {
                playerBlack = make_unique<Human>(0)
            } else {
                int level = stoi(player2.substr(9)); // The number
                playerBlack = make_unique<Computer>(0, level);
            }

            // We are always gonna have to setup players anyways
            cb.setupPlayers(playerWhite, playerBlack);
            if(!usedSetup()) cb.defaultBoard();
            // At this point, we have edited cb's game board already 
            // This set's cb's gameboard to a default baord. 
        
            string cmd2;
            while(cin >> cmd2) {

                if(cb.getTurn()) { //If passes means playerWhite turn
                    if (cmd2 == "move" && player1 == "human") {
                        string start, end;
                        cin >> start >> end;

                        int x = convertToInt(start.substr(0,1));
                        int y = (int) start.substr(1);
                        Vec coordinate1 = Vec{x,y};

                        int x = convertToInt(end.substr(0,1));
                        int y = (int) end.substr(1);
                        Vec coordinate2 = Vec{x,y};

                        if(cb.makeHumanMove(coordinate1, coordinate2)) {
                            // Valid Move
                            // Check if Pawn moved to either end of board depending on black or white. Dont really need to check if black end or white end cuz until this?
                            // Point, we are assuming they are valid moves
                            // what if they do move e2 e3 K, need to handle

                            if(cb.upgradePawn(coordinate2)) {
                                char newPiece;
                                cin >> newPiece;
                                cb.setupWithChar(newPiece, coordinate2);
                            } else cin.ignore();
                            // Ignore the single next character input by the user. 

                        } else {
                            cout << "Invalid move. Please retry" << endl;
                            // Invalid Move, try again!
                        }
                        // In makeHumanMove, we already check if move is valid. All we do inmain is just pass it.
                        // Is valid will check and determine based on what piece is located at start whether valid or not.  

                    } else if(cmd2 == "move" && player1 == "computer") {
                        // Make Computer Move
                        Vec end = cb.makeComputerMove(1, level);
                        if(cb.upgradePawn(end)){
                            cb.setupWithChar(newPiece, end);
                        }
                    } else if(cmd2 == "resign") {
                        //Player1 now has to lose 
                        // Create a chessboard function called forfeit that passes a bool. This function calls updateWhite or updateBlack depending on who won
                        // We pass who lost

                        cb.forfeit();
                        cb.restartGame();
                        // This function will update the white and black score and restart the chesboard.   
                        // I will then also restart the game
                    } 
                } else {
                    if (cmd2 == "move" && player2 == "human") {
                        string start, end;
                        cin >> start >> end;

                        string start, end;
                        cin >> start >> end;

                        int x = convertToInt(start.substr(0,1));
                        int y = (int) start.substr(1);
                        Vec coordinate1 = Vec{x,y};

                        int x = convertToInt(end.substr(0,1));
                        int y = (int) end.substr(1);
                        Vec coordinate2 = Vec{x,y};

                        if(cb.makeHumanMove(coordinate1, coordinate2)) {
                            if(cb.upgradePawn(coordinate2)) {
                                char newPiece;
                                cin >> newPiece;
                                cb.setupWithChar(newPiece, coordinate2);
                            } else cin.ignore();
                        } else {
                            cout << "Invalid move. Please retry" << endl;
                        }

                    } else if (cmd == "move" && player2 == "computer") {
                        Vec end = cb.makeComputerMove(0, level);
                        if(cb.upgradePawn(end)){
                            cb.setupWithChar(newPiece, end);
                        }
                    } else if(cmd2 == "resign") {
                        cb.forfeit();
                        cb.restartGame();
                    } 
                }

                // 1. Check if game is over
                if(cb.isEnd()) {
                    // isEnd has to also update black and white score
                    cb.restartGame();
                    // Does both reset gameboard and players
                    usedSetup = false;
                    break;
                }
                // If not, just continue prompting the user for input

            }
          // This for loop continuously gets input from the user regarding moves. 

        } else if (cmd == "setup") { // Input from players is solved by making the user enter game .
            string cmd2, coord, colour;
            char piece;

            cin >> cmd2;
            while(cin >> cmd2) {
                if(cmd2 == "+") {
                    cin >> piece >> coord;
                    // Place piece on coord. Piece is char
                    int x = convertToInt(piece.substr(0,1));
                    int y = (int) piece.substr(1);
                    Vec coordinate = Vec{x,y};
                    if (x == -1 ||(y <= 8 && y >= 1)) {
                        // Invalid input was pased. Do re-run the loop
                        cout << "Invalid Input" << endl;
                        break;
                    
                    }

                    if(piece == 'k') cb.setBlackKing(coordinate);
                    if(piece == 'K') cb.setWhiteKing(coordinate);

                    cb.setupWithChar(piece, coordinate); 
                } else if (cmd2 == "-") {
                    cin >> coord;
                    int x = convertToInt(piece.substr(0,1));
                    int y = (int) piece.substr(1);
                    // Remove a piece on a board by placing an empty piece on that coordinate
                    Vec coordinate = Vec{x,y};
                    cb.setupWithPiece(getEmptyPiece(coordinate), coordinate);
                } else if (cmd2 == "=") { 
                    // From my understanding, "makes it colors turn to go next" means when the game start, it is their turn
                    while (cin >> colour) {
                        if(colour == "black") {
                            // Chiara confirmed this is how it works. 
                            cb.setTurn(0); 
                            break;
                        } else if (colour == "white") {
                            cb.setTurn(1);
                            break;
                        } else {
                            cout << "Invalid input, please try again." << endl;
                        }
                    } 
                } else if (cmd == "done") { 
                    if(cb.isValid()) {
                        usedSetup = true;
                        break;
                        // Now a flag has been raised telling the main that the game has been setup with a gameboard.
                    }
                    cout << "Invalid Board Setup" << endl;
                    // Now we have to reset the board (as well as Players) and bring the uer all the way back up again. 
                    cb.restartGame();
                    break;
                }
            }
        } else { // Invalid Input
            cout << "Invalid Input, try Again" << endl;
            // At the beginning of the game, do we want to output to the user how to the game works/rules!!!! TO DO
        }
    } 
    // END OF GAME
    cout << game;
    // game has a output operator that will handle the displaying of the score
    cout << "Thank you for playing. We hope you enjoyed!" << endl;
    cout << "Make sure to play again!" << endl;
}

