#ifndef BOARD_H
#define BOARD_H

#include <cstdint>

#define FILE_A 0x0101010101010101ULL
#define FILE_B 0x0202020202020202ULL
#define FILE_G 0x4040404040404040ULL
#define FILE_H 0x8080808080808080ULL

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

void initBoard(Board &board);

#endif
