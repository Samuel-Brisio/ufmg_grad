#ifndef MY_CLIENT_H
#define MY_CLIENT_H

#include <string.h>
#include "common.h"
#include "game.h"

struct action simula_client(struct action act);
int get_command_code(char *command);
struct action client_input();
struct action parse_action(char *input);
int isActionValid(struct action act);


#endif