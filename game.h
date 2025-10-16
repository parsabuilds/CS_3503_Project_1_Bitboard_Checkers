#ifndef GAME_H
#define GAME_H

#include "bitboard.h"

// A struct to hold the entire game state using bitboards.
typedef struct {
    bitboard black_men;
    bitboard red_men;
    bitboard black_kings;
    bitboard red_kings;
    int is_blacks_turn;
} GameState;

// Sets up the bitboards for the starting positions.
void init_board(GameState* game);

// Renders the current board state in a human-readable format.
void display_board(const GameState* game);

// Validates and executes a player's move.
int make_move(GameState* game, int from, int to);

// Checks if a player has won the game.
int check_win_condition(const GameState* game);

#endif // GAME_H