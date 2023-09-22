#ifndef MY_COMMON_H
#define MY_COMMON_H

#include <stdio.h>

#define BOARD_N_ROWS 4
#define BOARD_N_COLS 4

struct action {
    int type;
    int coordinates[2];
    int board[BOARD_N_ROWS][BOARD_N_COLS];
};

struct game_action {
    int type;
    int coordinates[2];
};

void copy_matrix(int origin[BOARD_N_ROWS][BOARD_N_COLS], int dest[BOARD_N_ROWS][BOARD_N_COLS]);
void print_matrix(int board[BOARD_N_ROWS][BOARD_N_COLS]);
void print_board(int board[BOARD_N_ROWS][BOARD_N_COLS]);

#endif