#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h> // For uint64_t

// A 64-bit unsigned integer, perfect for an 8x8 board.
typedef uint64_t bitboard;

// Sets a bit at a given position to 1.
bitboard set_bit(bitboard board, int position);

// Clears a bit at a given position to 0.
bitboard clear_bit(bitboard board, int position);

// Returns the value of a bit (0 or 1) at a position.
int get_bit(bitboard board, int position);

// Counts the total number of set bits (pieces) on a board.
int count_bits(bitboard board);

// Displays the 64-bit integer in a binary format for debugging.
void print_binary(bitboard board);

#endif // BITBOARD_H