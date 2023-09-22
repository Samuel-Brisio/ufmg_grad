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
        for(size_t j = 0; j < BOARD_N_ROWS; ++j) {
            int number;
            fscanf(file, "%d,", &number);
            board.board[i][j] = number;
        }
    }

    fclose(file);
    load_game(board);
}

struct action receive_client_message(struct action act) {
    printf("--------------------------------------------\n");
    printf("Server\n");
    printf("Client Message Type: %d\n", act.type);
    printf("--------------------------------------------\n");

   
    switch (act.type)
    {   
    case 0:
        return server_start_game();
    case 1:
        return server_reveal_cell(act.coordinates);
    case 2:
        return server_flag_cell(act.coordinates);
    // Server -> Cliente
    // State -> Enviada pelo servidor ao cliente sempre que 
    // houver mudança no estado do board
    // case 3:
    //     server_start_game();
    //     break;
    case 4:
        return server_remove_flag(act.coordinates);
    case 5:
        return server_reset_game();
    // Server -> Cliente
    // Win -> Enviada pelo servidor ao cliente quando o jogo for ganho
    // case 6:
    //     server_start_game();
    //     break;
    // case 7:
    //     close_conection();
    //     break;
    // case 8:
    //     server_game_over();
    //     break;
    default:
        break;
    }
}

struct action server_remove_flag(int coord[2]) {
    struct action server_answer;
    server_answer.type = remove_flag(coord);
    copy_matrix(get_game_board().board, server_answer.board);

    return server_answer;
}

struct action server_flag_cell(int coord[2]) {
    struct action server_answer;
    server_answer.type = set_flag(coord);
    copy_matrix(get_game_board().board, server_answer.board);

    return server_answer;
}

struct action server_reveal_cell(int coord[2]) {
    printf("x: %d, y: %d\n", coord[0], coord[1]);
    
    struct action server_answer;
    server_answer.type = reveal_move(coord);

    // If Game Over
    if (server_answer.type == 8) copy_matrix(get_review_board().board, server_answer.board);
    else copy_matrix(get_game_board().board, server_answer.board);

    print_board(board_answer.board);   

    // send_to_client_board(server_answer);
    return server_answer;
}
 
int main() {
    load_input("/home/samuelbrisio/Documents/UFMG/Projetos_github/ufmg_grad/7_Semestre/Redes/TP1/input/board.txt");
    struct action server_msg;
    struct action client_msg;
    
    // Simula o inicio de jogo
    client_msg.type = 0;

    for(;;){
        server_msg = receive_client_message(client_msg);
        // printf("server_msg: %d\n", server_msg.type);
        client_msg = simula_client(server_msg);
        // printf("client_msg: %d\n", client_msg.type);

        if(client_msg.type == 7) {
            break;
        }
        else if(client_msg.type < 0) {
            printf("Erro menssage\n");
        }
    }

    printf("Hello, World\n");
    print_board(game_board.board);
    return 0;
}

struct action server_start_game() {
    start_game();
    struct action server_answer;
    server_answer.type = 3;
    copy_matrix(game_board.board, server_answer.board);
    return server_answer;

}

struct action server_reset_game() {
    reset_game();
    struct action server_answer;
    server_answer.type = 3;
    copy_matrix(get_game_board().board, server_answer.board);
    return server_answer;
}