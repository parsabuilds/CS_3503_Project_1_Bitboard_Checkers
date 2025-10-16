#include "game.h"
#include <stdio.h>
#include <stdlib.h>

// Sets up the bitboards for the starting positions.
void init_board(GameState* game) {
    game->black_men = 0ULL;
    game->red_men = 0ULL;
    game->black_kings = 0ULL;
    game->red_kings = 0ULL;

    // Set initial pieces for Black (top of the board)
    for (int i = 40; i < 64; i++) {
        int row = i / 8;
        int col = i % 8;
        // CORRECTED: Place pieces on active squares.
        if ((row + col) % 2 == 0) {
            game->black_men = set_bit(game->black_men, i);
        }
    }

    // Set initial pieces for Red (bottom of the board)
    for (int i = 0; i < 24; i++) {
        int row = i / 8;
        int col = i % 8;
        // CORRECTED: Place pieces on active squares.
        if ((row + col) % 2 == 0) {
            game->red_men = set_bit(game->red_men, i);
        }
    }
    game->is_blacks_turn = 0; // Red starts
}

// Renders the current board state in a human-readable format.
void display_board(const GameState* game) {
    printf("\n   _ _ _ _ _ _ _ _\n");
    for (int row = 7; row >= 0; row--) {
        printf(" %d|", row * 8);
        for (int col = 0; col < 8; col++) {
            int pos = row * 8 + col;
            char piece = ' ';
            // CORRECTED: Mark the correct squares as inactive.
            if ((row + col) % 2 != 0) {
                piece = '#'; // Inactive square
            } else {
                if (get_bit(game->black_men, pos)) piece = 'b';
                else if (get_bit(game->red_men, pos)) piece = 'r';
                else if (get_bit(game->black_kings, pos)) piece = 'B';
                else if (get_bit(game->red_kings, pos)) piece = 'R';
                else piece = '.'; // Empty active square
            }
            printf("%c ", piece);
        }
        printf("|\n");
    }
    printf("   _ _ _ _ _ _ _ _\n");
    printf("    0 1 2 3 4 5 6 7\n\n");
}

// A simple move validation and execution function.
int make_move(GameState* game, int from, int to) {
    if (from < 0 || from > 63 || to < 0 || to > 63) return 0; // Invalid square

    bitboard* current_men = game->is_blacks_turn ? &game->black_men : &game->red_men;
    bitboard* current_kings = game->is_blacks_turn ? &game->black_kings : &game->red_kings;
    bitboard* opponent_men = game->is_blacks_turn ? &game->red_men : &game->black_men;
    bitboard* opponent_kings = game->is_blacks_turn ? &game->red_kings : &game->black_kings;

    bitboard all_pieces = game->black_men | game->red_men | game->black_kings | game->red_kings;

    // Check if the 'from' square has the player's piece and 'to' is empty.
    if (!get_bit(*current_men | *current_kings, from) || get_bit(all_pieces, to)) {
        return 0;
    }
    
    int diff = abs(to - from);
    int is_king = get_bit(*current_kings, from);
    
    // Check for valid move or jump distance.
    if (diff != 7 && diff != 9 && diff != 14 && diff != 18) return 0;

    // Check move direction for men.
    if (!is_king) {
        if (game->is_blacks_turn && to > from) return 0; // Black men move down (decrease index)
        if (!game->is_blacks_turn && to < from) return 0; // Red men move up (increase index)
    }

    // Handle captures.
    if (diff == 14 || diff == 18) {
        int captured_pos = (from + to) / 2;
        // Check if opponent piece is on the captured square.
        if (get_bit(*opponent_men, captured_pos)) {
            *opponent_men = clear_bit(*opponent_men, captured_pos);
        } else if (get_bit(*opponent_kings, captured_pos)) {
            *opponent_kings = clear_bit(*opponent_kings, captured_pos);
        } else {
            return 0; // No piece to capture.
        }
    }

    // Move the piece.
    if (get_bit(*current_men, from)) {
        *current_men = clear_bit(*current_men, from);
        *current_men = set_bit(*current_men, to);
    } else { // It must be a king.
        *current_kings = clear_bit(*current_kings, from);
        *current_kings = set_bit(*current_kings, to);
    }
    
    // Handle king promotion.
    if (get_bit(*current_men, to)) {
        if (game->is_blacks_turn && to < 8) { // Black piece reached the end.
            *current_men = clear_bit(*current_men, to);
            *current_kings = set_bit(*current_kings, to);
        } else if (!game->is_blacks_turn && to > 55) { // Red piece reached the end.
            *current_men = clear_bit(*current_men, to);
            *current_kings = set_bit(*current_kings, to);
        }
    }

    return 1; // Successful move.
}

// Checks if a player has won the game.
int check_win_condition(const GameState* game) {
    if (game->is_blacks_turn) {
        if (count_bits(game->red_men | game->red_kings) == 0) return 1; // Black wins
    } else {
        if (count_bits(game->black_men | game->black_kings) == 0) return 2; // Red wins
    }
    return 0; // No winner yet.
}