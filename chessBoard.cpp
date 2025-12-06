#include<iostream>
#include <cstdint>
#define FILE_A 0x0101010101010101ULL
#define FILE_H 0x8080808080808080ULL

using namespace std;
using U64 = uint64_t; // 64bit unsigned int

enum Color { WHITE, BLACK };

struct Board {
    // 12개의 기물 비트보드
    U64 whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing;
    U64 blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing;

    // 전체 occupancy
    U64 whiteOccupancy;
    U64 blackOccupancy;
    U64 allOccupancy;


    Color sideToMove;
    uint8_t castlingRights;   // 4bit: WK, WQ, BK, BQ
    int enPassantSquare;      // no Square = -1
    int halfmoveClock;
    int fullmoveNumber;
};

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
    board.castlingRights = 0b1111; // white kingside, shite queenside, black kingside, white queenside
    board.enPassantSquare = -1; // means none
    board.halfmoveClock = 0; // check the 50 rule
    board.fullmoveNumber = 1; // check the number of turns not necessary
};

U64 whitePawnMove(U64 whitePawn, U64 allOccupied, U64 blackOccupied){

    U64 empty = ~allOccupied; // check pieces
    U64 singlePush = (whitePawn<<8)&empty; 
    U64 doublePush = ((singlePush & 0x0000000000FF0000ULL) << 8) & empty; // double push at first move
    
    // when pawn takes other pieces
    U64 takePieceLeft = (whitePawn<<7) & blackOccupied & ~FILE_A;
    U64 takePieceRight = (whitePawn<<9) & blackOccupied & ~FILE_H;


    return singlePush | doublePush | takePieceLeft | takePieceRight;
};

U64 blackPawnMove(U64 blackPawn, U64 allOccupied, U64 whiteOccupied){

    U64 empty = ~allOccupied;
    U64 singlePush = (blackPawn>>8)&empty;
    U64 doublePush = ((singlePush & 0x0000FF0000000000ULL) >> 8) & empty;
    
    // when pawn takes other pieces
    U64 takePieceLeft = (blackPawn>>7) & whiteOccupied & ~FILE_A;
    U64 takePieceRight = (blackPawn>>9) & whiteOccupied & ~FILE_H;
    
    
    return singlePush | doublePush | takePieceLeft | takePieceRight;
};

U64 blackKingMove(U64 blackKing, U64 blackOccupancy){

    U64 canMove = ~blackOccupancy; // check team's pieces
    U64 goLeft = (blackKing >> 1) & canMove & ~FILE_A ;
    U64 goRight = (blackKing << 1) & canMove & ~FILE_H ;
    U64 goUp = (blackKing << 8) & canMove;
    U64 goDown = (blackKing >> 8) & canMove;
    U64 leftDownDiagnol = (blackKing >> 7) & canMove;
    U64 leftUpDiagnol = (blackKing << 7) & canMove;
    U64 rightDownDiagnol = (blackKing >> 9) & canMove;
    U64 leftDownDiagnol = (blackKing >> )


    return goLeft | goRight | goUp | goDown;

};

U64 whiteKingMove(U64 whiteKing, U64 whiteOccupancy){

    U64 canMove = ~whiteOccupancy; // check team's pieces
    U64 goLeft = (whiteKing<<1) & canMove & ~FILE_A ;
    U64 goRight = (whiteKing>>1) & canMove & ~FILE_H ;
    U64 goUp = (whiteKing<<8) & canMove;
    U64 goDown = (whiteKing>>8) & canMove;

    return goLeft | goRight | goUp | goDown;

};