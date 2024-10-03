#include "GameOfLife.h"

/**
 * @brief prints the current state of the game board.
 *
 * The function iterates through the board array and prints '^' for GEN1 cells,
 * '*' for GEN2 cells, '+' for ZOMBIE cells, ' ' for LAND cells, and '.' for ZLAND cells.
 * Different colors are used to represent each cell state based on its current and past state.
 *
 * input: board the two-dimensional array representing the game board.
 * 
 */
void printBoard(struct cell board[HEIGHT][WIDTH]){
    int i;
    int j;

    refresh();
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            if(board[i][j].current == GEN1){
                if(board[i][j].past == LAND){
                    attron(COLOR_PAIR(2));
                    mvprintw(i, j, "^");
                    attroff(COLOR_PAIR(2));
                }
                else if(board[i][j].past == ZLAND){
                    attron(COLOR_PAIR(5));
                    mvprintw(i, j, "^");
                    attroff(COLOR_PAIR(5));                   
                }
            }
            else if(board[i][j].current == GEN2){
                if(board[i][j].past == LAND){
                    attron(COLOR_PAIR(3));
                    mvprintw(i, j, "*");
                    attroff(COLOR_PAIR(3));
                }
                else if(board[i][j].past == ZLAND){
                    attron(COLOR_PAIR(6));
                    mvprintw(i, j, "*");
                    attroff(COLOR_PAIR(6));                   
                }
            }
            else if(board[i][j].current == ZOMBIE){
                if(board[i][j].past == LAND){
                    attron(COLOR_PAIR(1));
                    mvprintw(i, j, "+");
                    attroff(COLOR_PAIR(1));
                }
                else if(board[i][j].past == ZLAND){
                    attron(COLOR_PAIR(4));
                    mvprintw(i, j, "+");
                    attroff(COLOR_PAIR(4));                   
                }
            }
            else if(board[i][j].current == LAND){
                attron(COLOR_PAIR(3));
                mvprintw(i, j, " ");
                attroff(COLOR_PAIR(3));
            }
            else if(board[i][j].current == ZLAND){
                attron(COLOR_PAIR(4));
                mvprintw(i, j, ".");
                attroff(COLOR_PAIR(4));
            }
        }
    }
    refresh();
}
/**
 * @brief Initializes the game board from a file.
 *
 * This function reads the initial state of the game board from a file named "landBoard.txt".
 * The file contains a grid where each character represents the state of a cell: '4' for LAND, '5' for ZLAND and '6' for PIT.
 * The function reads each character from the file, converts it to an integer, and assigns the corresponding
 * state to the cells of the board.
 *
 * input: board the two-dimensional array representing the game board.
 *
 */
void initializeBoard(struct cell board[HEIGHT][WIDTH]){
    char stateC;
    int state = 0;
    int c = 0;
    int r = 0;
    FILE *initialBoard;
    
    initialBoard = fopen("landBoard.txt", "r");
    
    if(initialBoard == NULL){
        printw("Error opening file\n");
        return;
    }

    while(fscanf(initialBoard, "%c", &stateC) == 1){
        state = stateC - '0';
        board[r][c].past = state;
        c++;

        if(c >= WIDTH){
            r++;
            c = 0;

            #if defined(_WIN32) && (!defined(__unix__) || !defined(__unix) || (!defined(__APPLE__) && !defined(__MACH__)))
            fscanf(initialBoard, "%c", &stateC); /* reads carriage return from file in case of Windows */
            #endif
        }
    }
    fclose(initialBoard);
}

/* Functions */
/**
 * @brief initializes the game board from a file.
 *
 * This function reads the initial state of the game board from a file named "GameOfLife.txt".
 * The file contains a grid where '0' represents a dead cell and '1' represents an alive cell. The function reads each character from
 * the file, converts it to an integer 0 or 1 and assigns the corresponding state to the cells
 * of the board.
 *
 * input: board the two-dimensional array representing the game board.
 * 
 */
void startConfig(struct cell board[HEIGHT][WIDTH], int userChoise){
    int i;
    int j;
    char stateC;
    int state = 0;
    int c = 0;
    int r = 0;
    srand(time(NULL));

    if(userChoise == 1){
        FILE *fp;

        fp = fopen("GameOfLife.txt", "r");

        if(fp == NULL){
            printw("Error opening file\n");
            return;
        }

        while(fscanf(fp, "%c", &stateC) == 1){
            state = stateC - '0';
            board[r][c].current = state;
            c++;

            if(c >= WIDTH){
                r++;
                c = 0;

                #if defined(_WIN32) && (!defined(__unix__) || !defined(__unix) || (!defined(__APPLE__) && !defined(__MACH__)))
                fscanf(fp, "%c", &stateC); /* reads carriage return from file in case of Windows */
                #endif
            }
        }
        fclose(fp);
    }
    else{
        for(i = 0; i < HEIGHT; i++){
            for(j = 0; j < WIDTH; j++){
                board[i][j].current = rand() % 4 + 1;
            }
        }
    }
}