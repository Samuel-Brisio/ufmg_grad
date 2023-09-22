
#include "client.h"

struct action simula_client(struct action act) {
    struct action client_action;
    printf("********************************************************\n");
    printf("Cliente\n");
    printf("Action Type: %d\n", act.type);

    
    if (act.type == 0) {
        print_board(act.board);
        client_action = client_input();
    }
    else if (act.type == 3) {
        print_board(act.board);
        client_action = client_input();
    }
    else if (act.type == 6) {
        printf("YOU WIN!\n");
        print_board(act.board);
        client_action = client_input();
    }
    else if (act.type == 8) {
        printf("GAME OVER!\n");
        print_board(act.board);
        client_action = client_input();
    }
    else {
        printf("server answer: %d", act.type);
        client_action = client_input();
    }

    printf("********************************************************\n");
    return client_action;
}

int get_command_code(char *command) {
    if (strcmp(command, "start") == 0) 
    {
        return 0;
    } 
    else if (strcmp(command, "reveal") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "flag") == 0)
    {
        return 2;
    }
    else if (strcmp(command, "remove_flag") == 0)
    {
        return 4;
    }
    else if (strcmp(command, "reset") == 0)
    {
        return 5;
    }
    else if (strcmp(command, "exit") == 0)
    {
        return 7;
    }
    /* more else if clauses */
    else /* default: */
    {
        // printf("Comando Invalido\n");
        return -1;
    }
}

struct action client_input() {
    struct action client_action;
    char input_str[1000];
    
    do {
        // Le a entrada
        fgets(input_str, sizeof(input_str), stdin);

        // Faz o parsing da entrada do jogador
        client_action = parse_action(input_str);
    } while (!isActionValid(client_action));

    return client_action;
}

int isActionValid(struct action act) {
    switch (act.type)
    {
    //Start Command
    case 0:
        // printf("\n")
        return 1;
    // Reveal Command
    case 1:
        if (act.coordinates[0] >= BOARD_N_ROWS || act.coordinates[1] >= BOARD_N_COLS) {
            printf("error: invalid cell\n");
            return 0;
        }
        // cell already revealed
        if (get_game_board().board[act.coordinates[0]][act.coordinates[1]] >= 0 ) {
            printf("error: cell already revealed\n");
            return 0;
        }

        return 1;
    // Flag Command
    case 2:
        if (act.coordinates[0] >= BOARD_N_ROWS || act.coordinates[1] >= BOARD_N_COLS) {
            printf("error: invalid cell\n");
            return 0;
        }
        // cell already has a flag
        if (get_game_board().board[act.coordinates[0]][act.coordinates[1]] == -3 ) {
            printf("error: cell already has a flag\n");
            return 0;   
        }
        // cannot insert flag in revealed cell
        if (get_game_board().board[act.coordinates[0]][act.coordinates[1]] >= 0 ) {
            printf("error: cannot insert flag in revealed cell\n");
            return 0;   
        }
        return 1;
    // State -> Server Send This
    case 3:
        // printf("\n")
        return 1;
    // Remove Flag Command
    case 4:
        if (act.coordinates[0] >= BOARD_N_ROWS || act.coordinates[1] >= BOARD_N_COLS) {
            printf("error: invalid cell\n");
            return 0;
        }
        // cannot remove flag in revealed cell
        // But this error isn't important
        if (get_game_board().board[act.coordinates[0]][act.coordinates[1]] >= 0 ) {
            return 0;
        }
        return 1;
    // Reset Command
    case 5:
        // printf("\n")
        return 1;
    default:
        printf("error: command not found\n");
        return 0;
    }
}

struct action parse_action(char *input) {
    char command[50];
    int coord_x, coord_y;
    sscanf(input, "%s %d,%d", command, &coord_x, &coord_y);

    struct action client_action;
    client_action.type = get_command_code(command);
    client_action.coordinates[0] = coord_x;
    client_action.coordinates[1] = coord_y;

    return client_action;
}