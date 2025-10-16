#include <stdio.h>
#include "game.h"

int main() {
    GameState game;
    init_board(&game);

    int from, to;
    int winner = 0;

    printf("Welcome to BitBoard Checkers!\n");
    printf("Enter moves as two numbers: 'from_square to_square' (e.g., '11 18').\n");

    while (winner == 0) {
        display_board(&game);
        printf("Current Turn: %s\n", game.is_blacks_turn ? "Black ('b'/'B')" : "Red ('r'/'R')");
        printf("Enter move: ");

        if (scanf("%d %d", &from, &to) != 2) {
            printf("Invalid input. Please enter two numbers.\n");
            // Clear input buffer
            while(getchar() != '\n'); 
            continue;
        }

        if (make_move(&game, from, to)) {
            winner = check_win_condition(&game);
            game.is_blacks_turn = !game.is_blacks_turn; // Switch turns.
        } else {
            printf("--- INVALID MOVE ---\n");
        }
    }

    display_board(&game);
    if (winner == 1) {
        printf("GAME OVER: Black wins!\n");
    } else {
        printf("GAME OVER: Red wins!\n");
    }

    return 0;
}