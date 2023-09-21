#include "server.h"

void load_input(char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: file cannot be open");
        exit(1);
    }

    struct Board board;

    for(size_t i = 0; i < BOARD_N_ROWS; ++i)
    {
        for(size_t j = 0; j < BOARD_N_ROWS; ++j)
            fscanf(file, "%d", board.board[i] + j);
    }

    fclose(file);
    load_game(board);
}

int client_message(struct action act) {
    switch (act.type)
    {   
    case 0:
        server_start_game();
        break;
    case 1:
        server_reveal_cell(act.coordinates);
        break;
    case 2:
        server_flag_cell();
        break;
    // Server -> Cliente
    // State -> Enviada pelo servidor ao cliente sempre que 
    // houver mudança no estado do board
    // case 3:
    //     server_start_game();
    //     break;
    case 4:
        server_remove_flag();
        break;
    case 5:
        server_reset_game();
        break;
    // Server -> Cliente
    // Win -> Enviada pelo servidor ao cliente quando o jogo for ganho
    // case 6:
    //     server_start_game();
    //     break;
    case 7:
        close_conection();
        break;
    case 8:
        server_game_over();
        break;
    default:
        break;
    }
}

void server_start_game() {
    struct action server_answer;
    
    start_game();
    copy_matrix(get_game_board().board, server_answer.board);

    // state -> id: 3 ->  Enviada pelo servidor ao cliente
    // sempre que houver mudança no estado do board
    server_answer.type = 3;    
    send_to_client_board(server_answer);
}

int server_reveal_cell(int coord[2]) {
    int status = review_move(coord);
    
    if (handle_status(status)) return 1;

    struct action server_answer;
    copy_matrix(get_game_board().board, server_answer.board);
    // state -> id: 3 ->  Enviada pelo servidor ao cliente
    // sempre que houver mudança no estado do board
    server_answer.type = 3;    

    send_to_client_board(server_answer);

}
 
int main() {
    load_input("input/board.txt");
    print_board(board_answer.board);
    return 0;
}