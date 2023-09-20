#include "game.h"

struct Board show_board() {
    return game_board;
}

struct Board review_board() {
    return board_answer;
}

int reset_game() {
    for (int i = 0; i < BOARD_N_ROWS; i++) {
        for (int j = 0; i < BOARD_N_COLS; j++) {
            game_board.board[i][j] = -2;
        }
    }
    return 0;
}

// revelar célula fora do range do tabuleiro error:                 invalid cell                                        1
// comando inexistente error:                                       command not found                                   2
// revela uma célula já revelada error:                             cell already revealed                               3
// flag em uma célula já marcada error:                             cell already has a flag                             4
// flag em uma célula revelada error:                               cannot insert flag in revealed cell                 5

int do_action(struct game_action act) {
    switch (act.type)
    {
    // reveal
    case 1:
        return review_move(act.coordinates);
        break;
    // Coloca uma flag
    case 2:
        return set_flag(act.coordinates);
        break;
    // Remove uma flag
    case 4:
        return remove_flag(act.coordinates);
        break;
    // Reseta o Jogo
    case 5:
        return reset_game();
        break;
    
    default:
        break;
    }
}



// Revela uma celula
// Erros que podem aparecer
// revelar célula fora do range do tabuleiro error:                 invalid cell                                        1
// revela uma célula já revelada error:                             cell already revealed                               3
int review_move(int coordinates[2]) {
    // revelar célula fora do range do tabuleiro error
    if (coordinates[0] > BOARD_N_ROWS || coordinates[1] > BOARD_N_COLS) return 1;

    // cell already revealed
    if (game_board.board[coordinates[0]][coordinates[1]] >= 0 ) return 3;

    // cell has a bomb
    if (board_answer.board[coordinates[0]][coordinates[1]] == -1 ) return -1;

    game_board.board[coordinates[0]][coordinates[1]] = board_answer.board[coordinates[0]][coordinates[1]];

    return 0;
}

// // Coloca uma flag
// Erros que podem aparecer
// revelar célula fora do range do tabuleiro error:                 invalid cell                                        1
// flag em uma célula já marcada error:                             cell already has a flag                             4
// flag em uma célula revelada error:                               cannot insert flag in revealed cell                 5
int set_flag(int coordinates[2]) {
    // revelar célula fora do range do tabuleiro error
    if (coordinates[0] > BOARD_N_ROWS || coordinates[1] > BOARD_N_COLS) return 1;

    // cell already has a flag
    if (game_board.board[coordinates[0]][coordinates[1]] == -3 ) return 4;

    // cannot insert flag in revealed cell
    if (game_board.board[coordinates[0]][coordinates[1]] >= 0 ) return 5;

    game_board.board[coordinates[0]][coordinates[1]] = -3;

    return 0;
}


// Remove uma flag
// revelar célula fora do range do tabuleiro error:                 invalid cell                                        1
int remove_flag(int coordinates[2]) {
    // revelar célula fora do range do tabuleiro error
    if (coordinates[0] > BOARD_N_ROWS || coordinates[1] > BOARD_N_COLS) return 1;

    // cannot remove flag in revealed cell
    // But this error isn't important
    if (game_board.board[coordinates[0]][coordinates[1]] >= 0 ) return 0;

    game_board.board[coordinates[0]][coordinates[1]] = -2;
}