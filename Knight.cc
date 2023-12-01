#include "Knight.h"
#include "ChessBoard.h"
// Can just call the Piece's default constructor because no difference between Knight and Piece

Knight::Knight(Vec coordinate, char type, bool colour): Piece{coordinate, type, colour} {}
Knight::Knight(const Knight& other): Piece{other} {}

void Knight::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
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

    //cout << "knight" << endl;

    
// Actually, it shouldn't matter if it is black or white. 
// x is col 
// y is row 
    topRight1 = Vec{coordx + 1, coordy - 2};
    topRight2 = Vec{coordx + 2, coordy - 1};
        
    topLeft1 = Vec{coordx - 1, coordy - 2};
    topLeft2 = Vec{coordx - 2, coordy - 1};

    bottomRight1 = Vec{coordx + 2, coordy + 1};
    bottomRight2 = Vec{coordx + 1, coordy + 2};

    bottomLeft1 = Vec{coordx - 2, coordy + 1};
    bottomLeft2 = Vec{coordx - 1, coordy + 2};

    
    // Need to check if teammate or enemy team

    Vec move = topRight1;
    shared_ptr<Piece> p = pieceAt(gb,move);
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

shared_ptr<Piece> Knight::clone() const {
    return make_shared<Knight>(*this);
}


