#ifndef MY_COMMON_H
#define MY_COMMON_H

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

#endif