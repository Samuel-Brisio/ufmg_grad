#ifndef MY_SERVER_H
#define MY_SERVER_H

#include "stdio.h"
#include "stdlib.h"

#include "common.h"
#include "game.h"

void load_input();
int client_message(struct action act);
int server_reveal_cell(int coor[2]);
int server_flag_cell();
int server_remove_flag();
int server_reset_game();
int close_conection();
int server_game_over();
int send_to_client_board(struct action act);
int handle_status(int status);

#endif
