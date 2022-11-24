#ifndef GAME_OF_LIFE_GOL_H
#define GAME_OF_LIFE_GOL_H

#include <stdint.h>
#include <stdio.h>

#define BOARD_HEIGHT 5
#define BOARD_WIDTH 5

typedef uint8_t Board[BOARD_HEIGHT][BOARD_WIDTH];
typedef uint8_t (*BoardPtr)[BOARD_WIDTH];

enum CELL_STATE {
    DEAD,
    ALIVE
};

/**
 * Fills the board randomly.
 *
 * @param board The board to fill
 * @param seed The seed to use. If 0, then the current time is used instead
 */
void board_init_random(BoardPtr board, uint32_t seed);

/**
 * Prints the board to an IO stream
 *
 * @param file IO stream to print to (defaults to 'stdout' if the argument is NULL)
 * @param board pointer to the board
 */
void board_print(FILE *file, BoardPtr board);

/**
 * Calculates how many live neighbors the cell has
 *
 * @param board The board on which the cell resides
 * @param cell_y Cell Y coordinate on the board
 * @param cell_x Cell X coordinate on the board
 *
 * @return Number of live neighbors around the cell
 */
uint8_t cell_count_neighbors(BoardPtr board, size_t cell_y, size_t cell_x);


/**
 * Calculates what state (DEAD or ALIVE) the cell
 * should be in the next generation.
 *
 * @param board The board on which the cell resides
 * @param cell_y Cell's Y coordinate on the board
 * @param cell_x Cell's X coordinate on the board
 *
 * @return 0 (DEAD) or 1 (ALIVE)
 */
uint8_t cell_calc_new_state(BoardPtr board, size_t cell_y, size_t cell_x);

/**
 * Fills the new board with the next generation of cells
 *
 * @param current The current board with cells
 * @param new The board to fill with the next generation cells
 *
 * @return Number of live cells in the new generation
 */
uint32_t board_new_generation(BoardPtr current, BoardPtr new);

#endif /* GAME_OF_LIFE_GOL_H */


