/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

/* Definitions and Constants */
#define HEIGHT 30
#define WIDTH 120

enum {DEAD, GEN1, GEN2, ZOMBIE, LAND, ZLAND, PIT};

struct cell {
    int past;
    int current;
    int future;
};

void initializeBoard(struct cell board[HEIGHT][WIDTH]);
void startConfig(struct cell board[HEIGHT][WIDTH], int userChoise);
void printBoard(struct cell board[HEIGHT][WIDTH]);
void countNeighbors(struct cell board[HEIGHT][WIDTH], int row, int column, int *gen1Neighbors, int *gen2Neighbors, int *zombieNeighbors);
void updateBoard(struct cell board[HEIGHT][WIDTH]);