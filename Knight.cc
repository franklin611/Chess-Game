#include "Knight.h"
#include "ChessBoard.h"

Knight::Knight(Vec coordinate, char type, bool colour): Piece{coordinate, type, colour} {}

Knight::Knight(const Knight& other): Piece{other} {}

// The possibleMoves of the knight based on the current gameboard
void Knight::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    // The different moves the knight can take (The different L shaped moves)
    Vec topRight1;
    Vec topRight2;
    Vec topLeft1;
    Vec topLeft2;
    Vec bottomRight1;
    Vec bottomRight2;
    Vec bottomLeft1;
    Vec bottomLeft2;
    int coordx = coordinate.getX();
    int coordy = coordinate.getY();

    topRight1 = Vec{coordx + 1, coordy - 2};
    topRight2 = Vec{coordx + 2, coordy - 1};
        
    topLeft1 = Vec{coordx - 1, coordy - 2};
    topLeft2 = Vec{coordx - 2, coordy - 1};

    bottomRight1 = Vec{coordx + 2, coordy + 1};
    bottomRight2 = Vec{coordx + 1, coordy + 2};

    bottomLeft1 = Vec{coordx - 2, coordy + 1};
    bottomLeft2 = Vec{coordx - 1, coordy + 2};


    Vec move = topRight1;
    shared_ptr<Piece> p = pieceAt(gb,move);
    // For each of the above L shaped moves, checks if the move is in bounds, and that
    // there is an empty piece there or an enemy piece
    if(inBounds(move) && isEmptyPiece(p)) {
        possibleMoves.push_back(move);
    } else if (inBounds(move) && (p->getTeam() != getTeam())) {
        possibleMoves.push_back(move);
    } 
    move = topRight2;
    p = pieceAt(gb,move);
    if(inBounds(move) && isEmptyPiece(p)) {
        possibleMoves.push_back(move);
    } else if (inBounds(move) && (p->getTeam() != getTeam())) {
        possibleMoves.push_back(move);
    } 

    move = topLeft1;
    p = pieceAt(gb,move);
    if(inBounds(move) && isEmptyPiece(p)) {
        possibleMoves.push_back(move);
    } else if (inBounds(move) && (p->getTeam() != getTeam())) {
        possibleMoves.push_back(move);
    } 

    move = topLeft2;
    p = pieceAt(gb,move);
    if(inBounds(move) && isEmptyPiece(p)) {
        possibleMoves.push_back(move);
    } else if (inBounds(move) && (p->getTeam() != getTeam())) {
        possibleMoves.push_back(move);
    } 

    move = bottomRight1;
    p = pieceAt(gb,move);
    if(inBounds(move) && isEmptyPiece(p)) {
        possibleMoves.push_back(move);
    } else if (inBounds(move) && (p->getTeam() != getTeam())) {
        possibleMoves.push_back(move);
    } 

    move = bottomRight2;
    p = pieceAt(gb,move);
    if(inBounds(move) && isEmptyPiece(p)) {
        possibleMoves.push_back(move);
    } else if (inBounds(move) && (p->getTeam() != getTeam())) {
        possibleMoves.push_back(move);
    } 

    move = bottomLeft1;
    p = pieceAt(gb,move);
    if(inBounds(move) && isEmptyPiece(p)) {
        possibleMoves.push_back(move);
    } else if (inBounds(move) && (p->getTeam() != getTeam())) {
        possibleMoves.push_back(move);
    } 

    move = bottomLeft2;
    p = pieceAt(gb,move);
    if(inBounds(move) && isEmptyPiece(p)) {
        possibleMoves.push_back(move);
    } else if (inBounds(move) && (p->getTeam() != getTeam())) {
        possibleMoves.push_back(move);
    } 
    
}

// Deep clone of the Knight
shared_ptr<Piece> Knight::clone() const {
    return make_shared<Knight>(*this);
}
