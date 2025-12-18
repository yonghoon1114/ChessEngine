#ifndef MAKE_MOVES_H
#define MAKE_MOVES_H
#include <vector>
#include "board.h"
#include "moves.h"

using namespace std;
    struct Move
    {
        int from;       // 0~63
        int to;         // 0~63
        Piece piece;      // PAWN, KNIGHT, ...
        Piece captured;   // NONE or piece type
        Piece promotion;  // NONE or QUEEN/ROOK/...
    };
    
    void generateMoves(const Board &board, vector<Move> &moveList);


#endif