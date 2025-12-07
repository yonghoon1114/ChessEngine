#ifndef MOVES_H
#define MOVES_H

#include "board.h"

U64 whitePawnMove(U64 whitePawn, U64 allOccupied, U64 blackOccupied);
U64 blackPawnMove(U64 blackPawn, U64 allOccupied, U64 whiteOccupied);
U64 kingMove(U64 king, U64 blackOcc, U64 whiteOcc, int color);
U64 knightMoves(U64 knight, U64 blackOcc, U64 whiteOcc, int color);

#endif
