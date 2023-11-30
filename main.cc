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


int convertToInt(char c) {
    if(c >= 'a' && c <= 'h') {
        return (c - 'a'); // 'a' is equal to 97
        // We use 0-7
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
    bool usedSetup = false;
    // ChessBoard cb; // Default chessBoard constructor
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

        if(cmd == "game") {
            //To setup a new game, we take two input playerWhite playerBlack.
            // They are not players, they are Observers
            // Observer -> Player -> Computer or Human. They are subclasses of Observer
            string player1, player2;
            cin >> player1 >> player2;
            shared_ptr<Observer> playerWhite, playerBlack;
            int level;
            if(!usedSetup) cb->defaultBoard(); // In both cases setup board first

            if(player1 == "human") {
                playerWhite = make_shared<Human>(1, cb);
            } else {
                level = stoi(player1.substr(9)); // Not sure if we can use stoi But this should level = the number in the brackets
                playerWhite = make_shared<Computer>(1, cb, level);
            }
            if(player2 == "human") {
                playerBlack = make_shared<Human>(0, cb);
            } else {
                level = stoi(player2.substr(9)); // The number
                playerBlack = make_shared<Computer>(0, cb, level);
            }


            cb->setupPlayers(playerWhite, playerBlack); // Then players
            string cmd2;
            while(cin >> cmd2) {

                if(cb->getTurn()) { //If passes means playerWhite turn
                    if (cmd2 == "move" && player1 == "human") {
                        string start, end;
                        cin >> start >> end;

                        int x = convertToInt(start.substr(0,1)[0]);
                        int y = stoi(start.substr(1));;
                        Vec coordinate1 = Vec{x, y - 1};

                        int x2 = convertToInt(end.substr(0,1)[0]);
                        int y2 = stoi(end.substr(1));
                        Vec coordinate2 = Vec{x2, y2 - 1};

                        auto humanWhite = dynamic_pointer_cast<Human>(cb->getPlayerWhite());

                        if(humanWhite->makeHumanMove(coordinate1, coordinate2)) {
                            // Valid Move
                            if(cb->upgradePawn(coordinate2)) {
                                char newPiece;
                                cin >> newPiece;
                                cb->setupWithChar(newPiece, coordinate2);
                            } else cin.ignore();
                            // cin.ignore(std::numeric_limits<std::streamsize>::max()); // ChatGPT suggested
                            // Ignore the single next character input by the user. (Cuz we can't assume just one character)
                            cout << cb;

                        } else {
                            cout << "Invalid move. Please retry" << endl;
                        }
                    } else if(cmd2 == "move" && player1 == "computer") {
                        // Make Computer Move

                        auto computerWhite = dynamic_pointer_cast<Computer>(cb->getPlayerWhite());
                        int level = computerWhite->getLevel();

                        Vec end = computerWhite->makeComputerMove(level); // TO DO UPDATE WITH HELENA'S NEW FUNCTION
                        if(cb->upgradePawn(end)){
                            cb->setupWithChar('Q', end);
                        }
                        cout << cb;
                    } else if(cmd2 == "resign") {
                        //Player1 now has to lose
                        cb->forfeit(); // This function will update the white and black score
                        cb->restartGame(); // Restart match
                    }
                } else {
                    if (cmd2 == "move" && player2 == "human") {
                        string start, end;
                        cin >> start >> end;

                        int x = convertToInt(start.substr(0,1)[0]);
                        int y = stoi(start.substr(1));
                        Vec coordinate1 = Vec{x, y - 1};

                        int x2 = convertToInt(end.substr(0,1)[0]);
                        int y2 = stoi(end.substr(1));
                        Vec coordinate2 = Vec{x2, y2 - 1}; // Start at row 0
                        
                        auto humanBlack = dynamic_pointer_cast<Human>(cb->getPlayerBlack());

                        if(humanBlack->makeHumanMove(coordinate1, coordinate2)) {
                            if(cb->upgradePawn(coordinate2)) {
                                char newPiece;
                                cin >> newPiece;
                                cb->setupWithChar(newPiece, coordinate2);
                            } else cin.ignore();
                            cout << cb;
                        } else {
                            cout << "Invalid move. Please retry" << endl;
                        }
                    } else if (cmd == "move" && player2 == "computer") {

                        auto computerBlack = dynamic_pointer_cast<Computer>(cb->getPlayerWhite());
                        int level = computerBlack->getLevel();

                        Vec end = computerBlack->makeComputerMove(level);
                        if(cb->upgradePawn(end)){
                            cb->setupWithChar('q', end);
                        }
                        cout << cb;
                    } else if(cmd2 == "resign") {
                        // Player2 has to lose
                        cb->forfeit();
                        cb->restartGame();
                    }
                }
                // // 1. Check if game is over
                // if(cb.isEnd()) { // will check players legalMoves to see if they are empoty or not
                //     cb.restartGame(); // Restarts ChessBoard
                //     // We don't need to reset player pointers because they will go out of scope or when we make it equal to something new, the old ones die
                //     usedSetup = false;
                //     break;
                // } // No longer needed
            }
        } else if (cmd == "setup") {
            string cmd2, coord, colour;
            char piece;

            while(cin >> cmd2) {
                if(cmd2 == "+") {
                    cin >> piece >> coord;
                    // e1, is Column 3 (starting from  0 to 7), Row 0
                    //  sop shoudl Vec{0,7)}
                    int x = convertToInt(coord.substr(0,1)[0]);
                    int y = stoi(coord.substr(1));
                    Vec coordinate = Vec{x, y- 1};
                    // Need to also check that the char was a proper input
                    if (x == -1 ||(y > 7 && y < 0) && !(piece == 'k' || piece == 'K' || piece == 'q' || piece == 'Q' ||
                        piece == 'b' || piece == 'B' || piece == 'n' || piece == 'N' ||
                        piece == 'r' || piece == 'R' || piece == 'p' || piece == 'P')) {
                        cout << "Invalid Input" << endl;
                        // I should not be breaking. I should be in the while loop waiting for commands
                    }
                    if(piece == 'k') cb->setBlackKing(coordinate);
                    if(piece == 'K') cb->setWhiteKing(coordinate);
                    cb->setupWithChar(piece, coordinate);
                    cout << cb;
                } else if (cmd2 == "-") {
                    cin >> coord;
                    int x = convertToInt(coord.substr(0,1)[0]);
                    int y = stoi(coord.substr(1));
                    // Remove a piece on a board by placing an empty piece on that coordinate
                    Vec coordinate = Vec{x, y - 1}; // We have to minus one because we are 0-7
                    cb->setupWithPiece(cb->getEmptyPiece(coordinate), coordinate);
                } else if (cmd2 == "=") {
                    // From my understanding, "makes it colors turn to go next" means when the game start, it is their turn
                    while (cin >> colour) {
                        if(colour == "black") {
                            cb->setTurn(0);
                        } else if (colour == "white") {
                            cb->setTurn(1);
                        } else {
                            cout << "Invalid input, please try again." << endl;
                        }
                    }
                    cout << cb;
                } else if (cmd == "done") {
                    if(cb->boardIsValid()) {
                        usedSetup = true;
                        break; // Only case where we break
                        // Now a flag has been raised telling the main that the game has been setup with a gameboard.
                    }
                    cout << "Invalid Board Setup" << endl;
                    // Now we have to reset the board (as well as Players) and bring the user all the way back up again.
                    cb->restartGame();
                    break;
                }
            }
        } else { // Invalid Input
            cout << "Invalid Input, try Again" << endl;
        }
    }
    // END OF GAME
    cout << cb;
    cout << "Thank you for playing. We hope you enjoyed!" << endl;
    cout << "Make sure to play again!" << endl;
    return 0;
}

