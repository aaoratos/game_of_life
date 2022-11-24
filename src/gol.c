#include "gol.h"
#include <stdlib.h>
#include <time.h>

void board_init_random(BoardPtr board, uint32_t seed) {
    size_t h, w;
    if (seed) srand(seed);
    else srand((uint32_t) time(NULL));
    for (h = 0; h < BOARD_HEIGHT; h++) {
        for (w = 0; w < BOARD_WIDTH; w++) {
            board[h][w] = (uint8_t) (rand() % 2);
        }
    }
}

void board_print(FILE *stream, BoardPtr board) {
    size_t h, w;
    if (!stream) stream = stdout;
    for (h = 0; h < BOARD_HEIGHT; h++) {
        for (w = 0; w < BOARD_WIDTH; w++) {
            fprintf(stream, "%c%c",
                    board[h][w] ? 'o' : '.',
                    w + 1 == BOARD_WIDTH ? '\n' : ' ');
        }
    }
}

uint8_t cell_count_neighbors(BoardPtr board, size_t cell_y, size_t cell_x) {
    int i, j;
    int dy, dx;
    uint8_t score = 0;
    for (i = -1; i < 2; i++) {
        dy = (int) cell_y + i;
        if (dy < 0 || dy >= BOARD_HEIGHT) continue;
        for (j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue;
            dx = (int) cell_x + j;
            if (dx < 0 || dx >= BOARD_WIDTH) continue;
            score += board[dy][dx];
        }
    }
    return score;
}

uint8_t cell_calc_new_state(BoardPtr board, size_t cell_y, size_t cell_x) {
    uint8_t current_state = board[cell_y][cell_x];
    uint8_t score = cell_count_neighbors(board, cell_y, cell_x);
    /* Any live cell with two or three live neighbours survives. */
    if (current_state == ALIVE && (score == 2 || score == 3)) return ALIVE;
    /* Any dead cell with three live neighbours becomes a live cell. */
    if (current_state == DEAD && score == 3) return ALIVE;
    /* All other live cells die in the next generation.
     * Similarly, all other dead cells stay dead. */
    return DEAD;
}

uint32_t board_new_generation(BoardPtr current, BoardPtr new) {
    size_t h, w;
    uint32_t alive_cells = 0;
    for (h = 0; h < BOARD_HEIGHT; h++) {
        for (w = 0; w < BOARD_WIDTH; w++) {
            new[h][w] = cell_calc_new_state(current, h, w);
            alive_cells += new[h][w];
        }
    }
    return alive_cells;
}
