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




int main() {
    string cmd;
    // ChessBoard cb;
    Xwindow xw;

    while (cin >> cmd) {
        // I would outpu to the user 1. What the game in a cool design 2. The rules of the game 
        
        if(cmd == "game") {
            //To setup a new game, we take two input playerWhite playerBlack.
            String player1, player2;
            cin >> player1 >> player2;

            // There must be a more efficient way to this i wont even lie
            if(player1 == "human") {
                Player playerWhite = Human{1};
            } else {
                // computer[1]
                int level = player1[9] // The number
                Player playerWhite = Computer{1,level};
            }
            if(player2 == "human") {
                Player playerBlack = Human{0};
            } else {
                // computer[1]
                int level = player2[9] // The number
                Player playerWhite = Computer{1,level};
            }
            string cmd2;


            //For chessboard, we now have our players.
            // Need to keep track of the input whether they are playerWhite or playerBlack
            // As well as if its a computer's turn or not
            chessBoard{playerWhite, playerBlack} cb;
            while(cin >> cmd2) { // This would be the word move.
                if(cb.getTurn()) { //If passes means playerWhite turn
                    if (player1 == "human") {
                        string start, end;
                        cin >> start >> end;
                        // Make Player1 do a move - TO DO - As well as check if the move is valid, do we need to do it here
                        // TO DO - As well determine the pieces on start and where it wants to go so that if it is necessary pawn promotion, get another input
                    } else if(cmd2 == "resign") {
                        //Player1 now has to lose 
                        player1.setCheckmate(true); // Set player's checkmate field to be true
                        if(end()) { // If this is true, this means the game can end. But I dont think so since the game already should be over since player1.setCheckmate is set to true
                            // What even needs to be done here? -TO DO
                        }


                    } else {
                        // Maker Player1 do a move as a Computer
                    }
                } else {
                    if (player2 == "human") {
                        string start, end;
                        cin >> start >> end;
                        // Make Player2 do a move - TO DO
                    } else if(cmd2 == "resign") {
                        player2.setCheckmate(true);
                        if(end()) {
                            // TO DO
                        }

                    } else {
                        // Maker Player2 do a move as a Computer
                    }
                }
                

            } // This for loop continuously gets input from the user regarding moves. 




        } else if (cmd == "setup") { // Enters setup mode TO DO : Where do we get user input for players?
            string cmd2, coord, colour;
            char piece;
            Chessboard cb;

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
                    cb.setupWithChar(piece, coordinate);
                    // Can't think of anything else here
                } else if (cmd2 == "-") {
                    cin >> coord;
                    int x = convertToInt(piece.substr(0,1));
                    int y = (int) piece.substr(1);
                    // How do we want to remove pieces. I guess we can signify by passing empty to Piece?
                    // We need to place an empty piece there.
                    // Even if we get the empty piece at this vec Coord, how do we actually put this piece on the chessboard. 
                    // I think we have to be able to pass a _ and a " " to setup to set up a white or black piece. 
                    Vec coordinate = Vec{x,y};
                    cb.setupWithPiece(getEmptyPiece(coordinate), coordinate);


                    // cb.setup('', Vec{x,y}); Might not even need setup, We could use the empty board to crossreference? TO DO

                } else if (cmd2 == "=") { 
                    // From my understanding, "makes it colors turn to go next" means when the game start, it is their turn
                    while (cin >> colour) {
                        if(colour == "black") {
                            // Set black turn to true.
                            cb.setTurn(0); // Set turn to 0, indicating black?  TO DO
                            break;


                        } else if (colour == "white") {
                            cb.setTurn(1);
                            break;

                        } else {
                            // They have inputted invalid input
                            // Prompt them for input again. 
                            cout << "Invalid input, please try again." << endl;
                        }
                    }
                    
                } else { // User has entered "done" to leave setup mode. 
                // 1. Need to check the current state of the board to see if it is valid. If not,  make them re-set up?  TO DO ASKED PIAZZA
                // Piazza said we had creative freedom. I personally think it is better to have a resetBoard. 
                // resetBoard();
                // break; 
                // Prompt the user with the rules and ask to start and try again.

                    if(ValidBoard()) { //
                        break;
                    }
                }

            }
        } else { // Invalid Input
            cout << "Invalid Input, try Again" << endl;
            // At the beginning of the game, do we want to output to the user how to the game works/rules!!!! TO DO

        }
    

    }
}

