#include <iostream>
#include "board.h"
#include "moves.h"

using namespace std;

void printBitboard(U64 bb) {
    for (int rank = 7; rank >= 0; rank--) {   // 8 → 1 rank
        for (int file = 0; file < 8; file++) { // a → h file
            int square = rank * 8 + file;
            U64 mask = 1ULL << square;

            if (bb & mask)
                cout << " 1";
            else
                cout << " .";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    Board board;
    initBoard(board);

    printBitboard(board.blackPawns);
    printBitboard(knightMoves(board.blackKnights, board.blackOccupancy, board.whiteOccupancy, BLACK));
    printBitboard(knightMoves(board.whiteKnights, board.blackOccupancy, board.whiteOccupancy, WHITE));
    return 0;
}

