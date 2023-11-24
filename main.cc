#include <iostream>
#include <string>
using namespace std;

int main() {
    string cmd;
    // ChessBoard cb;
    Xwindow xw;

    while (cin >> cmd) {
        
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
                        // Make Player1 do a move - TO DO
                    } else if(cmd2 == "resign") {
                        //Player1 now has to lose 
                        
                    }
                    } else {
                        // Maker Player1 do a move as a Computer
                    }
                } else {
                    if (player2 == "human") {
                        string start, end;
                        cin >> start >> end;
                        // Make Player2 do a move - TO DO
                    } else {
                        // Maker Player2 do a move as a Computer
                    }
                }
                

            }




        }

    }
}