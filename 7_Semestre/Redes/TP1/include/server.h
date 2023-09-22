#ifndef MY_SERVER_H
#define MY_SERVER_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "common.h"
#include "game.h"
#include "client.h"

void load_input();
struct action receive_client_message(struct action act);
struct action server_reveal_cell(int coor[2]);
struct action server_flag_cell(int coord[2]);
struct action server_remove_flag(int coord[2]);
struct action server_reset_game();
int close_conection();
struct action server_game_over();
int send_to_client_board(struct action act);
int handle_status(int status);
struct action server_start_game();

// Apagar
struct action simula_client(struct action act);
int get_command_code(char *command);

#endif
