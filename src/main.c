#include "gol.h"

int main(void) {
    int key;
    Board swap_board;
    Board main_board = {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
    };
    BoardPtr main_board_ptr = &main_board[0];
    BoardPtr swap_board_ptr = &swap_board[0];
    BoardPtr tmp_board_ptr = NULL;
    do {
        board_print(NULL, main_board_ptr);
        key = getchar();
        board_new_generation(main_board_ptr, swap_board_ptr);
        tmp_board_ptr = main_board_ptr;
        main_board_ptr = swap_board_ptr;
        swap_board_ptr = tmp_board_ptr;
    } while (key != 'q');
    return 0;
}
