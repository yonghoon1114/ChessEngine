#include "board.h"

void initBoard(Board &board){
    board.whitePawns   = 0x000000000000FF00ULL; // 2nd rank
    board.whiteRooks   = 0x0000000000000081ULL; // a1, h1
    board.whiteKnights = 0x0000000000000042ULL; // b1, g1
    board.whiteBishops = 0x0000000000000024ULL; // c1, f1
    board.whiteQueens  = 0x0000000000000008ULL; // d1
    board.whiteKing    = 0x0000000000000010ULL; // e1

    board.blackPawns   = 0x00FF000000000000ULL; // 7th rank
    board.blackRooks   = 0x8100000000000000ULL; // a8, h8
    board.blackKnights = 0x4200000000000000ULL; // b8, g8
    board.blackBishops = 0x2400000000000000ULL; // c8, f8
    board.blackQueens  = 0x0800000000000000ULL; // d8
    board.blackKing    = 0x1000000000000000ULL; // e8

    board.whiteOccupancy = board.whitePawns | board.whiteKnights | board.whiteBishops
                         | board.whiteRooks | board.whiteQueens | board.whiteKing;

    board.blackOccupancy = board.blackPawns | board.blackKnights | board.blackBishops
                         | board.blackRooks | board.blackQueens | board.blackKing;

    board.allOccupancy = board.whiteOccupancy | board.blackOccupancy;

    board.sideToMove = WHITE;
    board.castlingRights = 0b1111; // white kingside, white queenside, black kingside, black queenside
    board.enPassantSquare = -1; // means none
    board.halfmoveClock = 0; // check the 50 rule
    board.fullmoveNumber = 1; // check the number of turns not necessary
};
