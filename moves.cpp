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
    
    U64 ownPieces=0;
    if(color == WHITE){
        ownPieces = whiteOcc;
    }
    else{
        ownPieces = blackOcc;
    }

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