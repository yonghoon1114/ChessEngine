#include "moves.h"

U64 whitePawnMove(U64 whitePawn, U64 allOccupied, U64 blackOccupied){

    U64 empty = ~allOccupied; 
    U64 moves = 0;
    
    // single push
    moves |= (whitePawn<<8)&empty; 
    
    // double push (2 steps) → white pawn must be on rank 2
    moves |= ((whitePawn & 0x000000000000FF00ULL) << 16) & empty & (empty >> 8); 
    
    // captures
    moves |= (whitePawn << 7) & blackOccupied & ~FILE_A;
    moves |= (whitePawn << 9) & blackOccupied & ~FILE_H;

    return moves;
}

U64 blackPawnMove(U64 blackPawn, U64 allOccupied, U64 whiteOccupied){

    U64 empty = ~allOccupied;
    U64 moves = 0;

    // single push (1 step)
    moves |= (blackPawn >> 8) & empty;

    // double push (2 steps) → black pawn must be on rank 7
    moves |= ((blackPawn & 0x00FF000000000000ULL) >> 16) & empty & (empty >> 8);

    // captures
    moves |= (blackPawn >> 7) & whiteOccupied & ~FILE_H;
    moves |= (blackPawn >> 9) & whiteOccupied & ~FILE_A;

    return moves;
}

U64 kingMove(U64 king, U64 blackOcc, U64 whiteOcc, int color)
{
    U64 ownPieces = (color == 0) ? whiteOcc : blackOcc;

    U64 moves = 0;

    // left / right
    moves |= (king >> 1) & ~FILE_A;
    moves |= (king << 1) & ~FILE_H;

    // up / down
    moves |= (king << 8) ;
    moves |= (king >> 8);

    // diagonals
    moves |= (king << 7)  & ~FILE_H; // up-left
    moves |= (king << 9)  & ~FILE_A; // up-right
    moves |= (king >> 7) & ~FILE_A; // down-left
    moves |= (king >> 9)  & ~FILE_H; // down-right

    moves &= ~ownPieces;


    return moves;
}

U64 knightMoves(U64 knight, U64 blackOcc, U64 whiteOcc, int color){

    U64 ownPieces = (color == WHITE) ? whiteOcc : blackOcc;

    U64 moves = 0;
    
    // +2 up, +1 right
    moves |= (knight << 17) & ~FILE_A;
    // +2 up, -1 left
    moves |= (knight << 15)  & ~FILE_H;
    // +1 up, +2 right
    moves |= (knight << 10) & ~(FILE_A | FILE_B);
    // +1 up, -2 left
    moves |= (knight << 6)   & ~(FILE_G | FILE_H);
    // -2 down, -1 left
    moves |= (knight >> 17)  & ~FILE_H;
    // -2 down, +1 right
    moves |= (knight >> 15) & ~FILE_A;
    // -1 down, -2 left
    moves |= (knight >> 10)  & ~(FILE_H | FILE_G);
    // -1 down, +2 right
    moves |= (knight >> 6)   & ~(FILE_A | FILE_B);

    moves &= ~ownPieces;

    return moves;
}

U64 bishopMoves(U64 bishops, U64 blackOcc, U64 whiteOcc, int color) {
    U64 moves = 0;
    U64 own = (color == 0) ? whiteOcc : blackOcc;
    U64 opp = (color == 0) ? blackOcc : whiteOcc;
    U64 b = bishops;
    while (b) {
        // isolate a single rook
        U64 bishop = b & -b;
        b -= bishop;
        if(color == WHITE) {
            own = whiteOcc;
            opp = blackOcc;
        } else {
            own = blackOcc;
            opp = whiteOcc;
        }
        int from = __builtin_ctzll(bishop);  // rook square index 0~63
        int rank = from / 8;
        int file = from % 8;
        // up-right
        for (int r = rank + 1, f = file + 1; r < 8 && f < 8; ++r, ++f) {
            U64 bit = 1ULL << (r*8 + f);
            if (own & bit) break;
            moves |= bit;
            if (opp & bit) break;
        }
        // up-left
        for (int r = rank + 1, f = file - 1; r < 8 && f >= 0; ++r, --f) {
            U64 bit = 1ULL << (r*8 + f);
            if (own & bit) break;
            moves |= bit;
            if (opp & bit) break;
        }
        // down-right
        for (int r = rank - 1, f = file + 1; r >= 0 && f < 8; --r, ++f) {
            U64 bit = 1ULL << (r*8 + f);
            if (own & bit) break;
            moves |= bit;
            if (opp & bit) break;
        }
        // down-left
        for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; --r, --f) {
            U64 bit = 1ULL << (r*8 + f);
            if (own & bit) break;
            moves |= bit;
            if (opp & bit) break;
        }
    }
    return moves;
}



U64 rookMoves(U64 rooks, U64 blackOcc, U64 whiteOcc, int color) {
    U64 moves = 0;
    U64 ownPieces = 0;
    U64 oppPieces = 0;
    U64 rbb = rooks;

    while (rbb) {
        // isolate a single rook
        U64 rook = rbb & -rbb;
        rbb -= rook;
        if(color == WHITE) {
            ownPieces = whiteOcc;
            oppPieces = blackOcc;
        } else {
            ownPieces = blackOcc;
            oppPieces = whiteOcc;
        }
        int from = __builtin_ctzll(rook);  // rook square index 0~63

        int rank = from / 8;
        int file = from % 8;

        // 4 방향: ↑ ↓ → ←

        // ↑ (up)
        for (int r = rank + 1; r < 8; r++) {
            int sq = r * 8 + file;
            U64 bit = 1ULL << sq;

            // if it's our piece, stop
            if(ownPieces & bit) break;
            moves|= bit;
            // if it's opponent's piece, stop but include the square
            if (oppPieces & bit) break; // blocked
        }
        // down
        for (int r = rank - 1; r >= 0; r--) {
            int sq = r * 8 + file;
            U64 bit = 1ULL << sq;
            if (ownPieces & bit) break;
            moves |= bit;
            if (oppPieces & bit) break;
        }

        // right
        for (int f = file + 1; f < 8; f++) {
            int sq = rank * 8 + f;
            U64 bit = 1ULL << sq;
            if (ownPieces & bit) break;
            moves |= bit;
            if (oppPieces & bit) break;
        }

        // left
        for (int f = file - 1; f >= 0; f--) {
            int sq = rank * 8 + f;
            U64 bit = 1ULL << sq;
            if (ownPieces & bit) break;
            moves |= bit;
            if (oppPieces & bit) break;
        }
    }
    return moves;
}
U64 queenMoves(U64 queen, U64 blackOcc, U64 whiteOcc, int color) {
    U64 vertical = rookMoves(queen , blackOcc, whiteOcc, color); 
    U64 diagonal = bishopMoves(queen , blackOcc, whiteOcc, color);
    return vertical | diagonal;
}