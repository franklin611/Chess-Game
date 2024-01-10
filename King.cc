#include "King.h"

// default constructor 
King::King(Vec coordinate, char type, bool colour): Piece{coordinate, type, colour}, moved{false} {}

// default constructor 
King::King() : Piece{}, moved{false} {}

// copy constructor 
King::King(const King& other) : Piece{other}, moved{other.moved} {}

// updates if the king has moved
void King::hasMoved(){
    moved = true;
}

// accesses the king's moved boolean
bool King::getMoved() {
    return moved;
}

// Determines all the possible moves the King can take
void King::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec moveUp = Vec{coordinate.getX(), coordinate.getY() - 1};
    Vec moveLeft = Vec{coordinate.getX() - 1, coordinate.getY()};
    Vec moveRight = Vec{coordinate.getX() + 1, coordinate.getY()};
    Vec moveDown = Vec{coordinate.getX(), coordinate.getY() + 1};
    Vec topDiagonalLeft = Vec{coordinate.getX() - 1, coordinate.getY() - 1};
    Vec topDiagonalRight = Vec{coordinate.getX() + 1, coordinate.getY() - 1};
    Vec bottomDiagonalLeft = Vec{coordinate.getX() - 1 , coordinate.getY() + 1};
    Vec bottomDiagonalRight = Vec{coordinate.getX() + 1, coordinate.getY() + 1};

    Vec castleLeft = Vec{coordinate.getX() - 3, coordinate.getY()}; // NEW WITH NEW KING POSTION WHITE
    Vec castleRight = Vec{coordinate.getX() + 2, coordinate.getY()};
    
    // Vec castleLeft2 = Vec{coordinate.getX() + 3, coordinate.getY()}; // NEW WITH NEW KING POSTION BLACK
    // Vec castleRight2 = Vec{coordinate.getX() - 2, coordinate.getY()};

    shared_ptr<King> king = dynamic_pointer_cast<King>(gb[coordinate.getY()][coordinate.getX()]);

    Vec move;
    Vec move2;


    // Castle Right

    move = Vec{coordinate.getX() + 1, coordinate.getY()};
    move2 = Vec{coordinate.getX() + 2, coordinate.getY()};
    Vec move3 = Vec{coordinate.getX() + 3, coordinate.getY()};

    shared_ptr<Piece> p = pieceAt(gb,move);
    shared_ptr<Piece> p2 = pieceAt(gb,move2);
    
    // Checks that there is no pieces between the King and rook, checks that a castle move is in bounds, that both the rook and king have not moved
    // and that there is an actual King and Rook of the same team to castle with
    if (!moved &&  inBounds(move) && inBounds(move2) && inBounds(move3) && (!(king->getMoved()) && isEmptyPiece(p) && isEmptyPiece(p2))) {
        if ((pieceAt(gb, move3)->getType() == 'R' && getTeam()) || (pieceAt(gb, move3)->getType() == 'r' && !getTeam())) {
            possibleMoves.push_back(castleRight);
        }
    }


    move = Vec{coordinate.getX() - 1, coordinate.getY()};
    move2 = Vec{coordinate.getX() - 2, coordinate.getY()};
    move3 = Vec{coordinate.getX() - 3, coordinate.getY()};
    Vec move4 = Vec{coordinate.getX() - 4, coordinate.getY()};

    p = pieceAt(gb, move);
    p2 = pieceAt(gb, move2);
    shared_ptr<Piece> p3 = pieceAt(gb, move3);

    // We have to account for the 3 pieces to the right
    if (!moved && inBounds(move) && inBounds(move2) && inBounds(move3) && inBounds(move4) && (!(king->getMoved()) && isEmptyPiece(p) && isEmptyPiece(p2) && isEmptyPiece(p3))) {
        if ((pieceAt(gb, move4)->getType() == 'R' && getTeam()) || (pieceAt(gb, move4)->getType() == 'r' && !getTeam())) {
            possibleMoves.push_back(castleLeft);
        }
    }

    // // BLACK CASTLING
    // move = Vec{coordinate.getX() - 1, coordinate.getY()};
    // move2 = Vec{coordinate.getX() - 2, coordinate.getY()};
    // move3 = Vec{coordinate.getX() - 3, coordinate.getY()};

    // p = pieceAt(gb,move);
    // p2 = pieceAt(gb,move2);
    
    // // Checks that there is no pieces between the King and rook, checks that a castle move is in bounds, that both the rook and king have not moved
    // // and that there is an actual King and Rook of the same team to castle with
    // if (!moved &&  inBounds(move) && inBounds(move2) && inBounds(move3) && (!(king->getMoved()) && isEmptyPiece(p) && isEmptyPiece(p2))) {
    //     if ((pieceAt(gb, move3)->getType() == 'R' && getTeam()) || (pieceAt(gb, move3)->getType() == 'r' && !getTeam())) {
    //         possibleMoves.push_back(castleRight2);
    //     }
    // }


    // move = Vec{coordinate.getX() + 1, coordinate.getY()};
    // move2 = Vec{coordinate.getX() + 2, coordinate.getY()};
    // move3 = Vec{coordinate.getX() + 3, coordinate.getY()};
    // move4 = Vec{coordinate.getX() + 4, coordinate.getY()};

    // p = pieceAt(gb, move);
    // p2 = pieceAt(gb, move2);
    // p3 = pieceAt(gb, move3);

    // // We have to account for the 3 pieces to the right
    // if (!moved && inBounds(move) && inBounds(move2) && inBounds(move3) && inBounds(move4) && (!(king->getMoved()) && isEmptyPiece(p) && isEmptyPiece(p2) && isEmptyPiece(p3))) {
    //     if ((pieceAt(gb, move4)->getType() == 'R' && getTeam()) || (pieceAt(gb, move4)->getType() == 'r' && !getTeam())) {
    //         possibleMoves.push_back(castleLeft2);
    //     }
    // }

    // Determines if each of moves above is a valid move
    // It must either be an empty piece there, or it is an enemy piece there
    p = pieceAt(gb, moveUp);
    if (inBounds(moveUp) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(moveUp);
    }
    p = pieceAt(gb, moveLeft);
    if (inBounds(moveLeft) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(moveLeft);
    }
    p = pieceAt(gb, moveRight);
    if (inBounds(moveRight) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(moveRight);
    }
    p = pieceAt(gb, moveDown);
    if (inBounds(moveDown) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(moveDown);
    }
    p = pieceAt(gb, topDiagonalLeft);
    if (inBounds(topDiagonalLeft) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(topDiagonalLeft);
    }
    p = pieceAt(gb, topDiagonalRight);
    if (inBounds(topDiagonalRight) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(topDiagonalRight);
    }
    p = pieceAt(gb, bottomDiagonalLeft);
    if (inBounds(bottomDiagonalLeft) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(bottomDiagonalLeft);
    }
    p = pieceAt(gb, bottomDiagonalRight);
    if (inBounds(bottomDiagonalRight) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(bottomDiagonalRight);
    }
}

// Deep copy
shared_ptr<Piece> King::clone() const {
    return make_shared<King>(*this);
}
