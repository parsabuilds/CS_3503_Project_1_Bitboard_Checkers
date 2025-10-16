#include "bitboard.h"
#include <stdio.h>

// Sets a bit at a given position to 1.
bitboard set_bit(bitboard board, int position) {
    if (position < 0 || position > 63) return board; // Handle invalid positions.
    return board | (1ULL << position); // Use 1ULL for 64-bit operations.
}

// Clears a bit at a given position to 0.
bitboard clear_bit(bitboard board, int position) {
    if (position < 0 || position > 63) return board; // Handle invalid positions.
    return board & ~(1ULL << position);
}

// Returns the value of a bit (0 or 1) at a position.
int get_bit(bitboard board, int position) {
    if (position < 0 || position > 63) return 0;
    return (board >> position) & 1ULL;
}

// Counts the total number of set bits (pieces) on a board.
int count_bits(bitboard board) {
    int count = 0;
    for (int i = 0; i < 64; i++) {
        if (get_bit(board, i)) {
            count++;
        }
    }
    return count;
}

// Displays the 64-bit integer in a binary format for debugging.
void print_binary(bitboard board) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", get_bit(board, i));
        if (i % 8 == 0) printf("\n");
    }
    printf("\n");
}