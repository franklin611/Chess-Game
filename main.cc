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
            chessBoard{playerWhite, playerBlack} cb;

            string cmd2;
            while(cin >> cmd2) { 
                // 

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

                            if(cb.upgradePawn(coordinate2)) {
                                char newPiece;
                                cin >> newPiece;
                                cb.setupWithChar(newPiece, coordinate2);
                            }

                        } else {
                            // Invalid Move, try again!
                        }
                        // In makeHumanMove, we already check if move is valid. All we do inmain is just pass it.
                        // Is valid will check and determine based on what piece is located at start whether valid or not.  

                    } else if(cmd2 == "move" && player1 == "computer") {
                        // Make Computer Move
                        Vec end = cb.makeComputerMove(&playerWhite);
                        if(cb.upgradePawn(end)){
                            cb.setupWithChar(newPiece, end);
                        }
                    } else if(cmd2 == "resign") {
                        //Player1 now has to lose 
                        // Create a chessboard function called forfeit that passes a bool. This function calls updateWhite or updateBlack depending on who won
                        // We pass who lost

                        cb.forfeit(1);
                        // This function will update the white and black score and restart the chesboard.                   
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
                            }
                    } else if (cmd == "move" && player2 == "computer") {
                        Vec end = cb.makeComputerMove(&playerBlack);
                        if(cb.upgradePawn(end)){
                            cb.setupWithChar(newPiece, end);
                        }
                    } else if(cmd2 == "resign") {
                        cb.forfeit(0);
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
                } else { // User has entered "done" to leave setup mode. 
                // 1. Need to check the current state of the board to see if it is valid. If not,  make them re-set up?  TO DO ASKED PIAZZA
                // Piazza said we had creative freedom. I personally think it is better to have a resetBoard. 
                // resetBoard();
                // break; 
                // Prompt the user with the rules and ask to start and try again.

                    if(cb.ValidBoard()) { //
                        break;
                    } else {
                        cout << "Invalid Board Setup. Please re-setup again." << endl;
                        cout << "You had an extra blah blah" << endl; // Create logic for determining where it went wrong. We can do this in main or Chessboard -TO DO
                        // output invalid board and explain why it was
                        // Resetboard aned start from the very beginnign. Instef of very beginnign of "Welcome"
                        // Just to the point wher tehy were setting up the board again. But we have to start witha fresh board

                        // No break
                        cb.restartGame();
                    }
                }
            }
        } else { // Invalid Input
            cout << "Invalid Input, try Again" << endl;
            // At the beginning of the game, do we want to output to the user how to the game works/rules!!!! TO DO
        }
    }
}

