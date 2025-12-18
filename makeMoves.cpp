#include <vector>
#include "makeMoves.h"
#include "board.h"
#include "moves.h"

void generateMoves(const Board &board, vector<Move> &moveList) {
    moveList.clear();
    U64 fromBB, toBB;
    Move move;

    Color us = board.sideToMove;
    Color them = (us == WHITE) ? BLACK : WHITE;

    U64 ownPieces = (us == WHITE) ? board.whiteOccupancy : board.blackOccupancy;
    U64 oppPieces = (us == WHITE) ? board.blackOccupancy : board.whiteOccupancy;
    U64 allPieces = board.allOccupancy;

    fromBB = (us == WHITE) ? board.whitePawns : board.blackPawns;
    U64 pbb = fromBB;
    while (pbb) {
        U64 pawn = pbb & -pbb; // isolate a single pawn
        pbb -= pawn;
        int from = __builtin_ctzll(pawn); // pawn square index 0~63

        U64 possibleMoves = 0;
        if (us == WHITE) {
            possibleMoves = whitePawnMove(pawn, allPieces, oppPieces);
        } else {
            possibleMoves = blackPawnMove(pawn, allPieces, oppPieces);
        }

        U64 tbb = possibleMoves;
        while (tbb) {
            U64 toSquare = tbb & -tbb; // isolate a single target square
            tbb -= toSquare;
            int to = __builtin_ctzll(toSquare); // target square index 0~63

            move.from = from;
            move.to = to;
            move.piece = PAWN;
            move.captured = (oppPieces & toSquare) ? PAWN : NONE; // Simplified: assume capturing a pawn
            move.promotion = NONE; // Promotion handling can be added later

            moveList.push_back(move);
        }
    }

    // Similar logic can be applied for other pieces: KNIGHT, BISHOP, ROOK, QUEEN, KING