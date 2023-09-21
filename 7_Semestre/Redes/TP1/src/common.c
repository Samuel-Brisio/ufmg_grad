#include "common.h"

void copy_matrix(int origin[BOARD_N_ROWS][BOARD_N_COLS], int dest[BOARD_N_ROWS][BOARD_N_COLS]) {
    for (int i = 0; i < BOARD_N_ROWS; i++) {
        for (int j = 0; j < BOARD_N_COLS; i++) {
            dest[i][j] = origin[i][j];
        }
    }
}

void print_board(int board[BOARD_N_ROWS][BOARD_N_COLS]) {
    for (int i = 0; i < BOARD_N_ROWS; i++) {
        for (int j = 0; j < BOARD_N_COLS; i++) {
            if (j == BOARD_N_COLS - 1) printf("%d\n", board[i][j]);
            else printf("%d\t\t", board[i][j]);
        }
    }
}