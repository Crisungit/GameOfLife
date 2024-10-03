#include "GameOfLife.h"

/**
 * @brief Counts all the neighbor cells that are alive
 *
 * The function gets the inputs from the updateBoard function, inputs tells where we are in the 
 * tow dementional board. Itirates from the values -1 0 1 it egnores 0 because it's the column we 
 * are in right now, the newRow and newColumn are there to error controll so we dont read -1 or 
 * over board length. The function checks all the neighbors for both generations and adds upp all the alive ones to the 
 * corresponding counter that points to the updateBoard funktion.
 *
 * input: board the two-dimensional array representing the game board.
 * input: int row tells what row we are in the array.
 * input: int column tells what column we are in the array.
 * input: int *gen1Neighbors pointer to the counter for neighbors belonging to GEN1.
 * input: int *gen2Neighbors pointer to the counter for neighbors belonging to GEN2.
 * 
 *
 */
void countNeighbors(struct cell board[HEIGHT][WIDTH], int row, int column, int *gen1Neighbors, int *gen2Neighbors, int *zombieNeighbors){
    int gen1Counter = 0;
    int gen2Counter = 0;
    int zombieCounter = 0;
    int i;
    int j;
    int newRow;
    int newColumn; 

    for(i = -1; i <= 1; i++){
        for(j = -1; j <= 1; j++){
            
            newRow = row + i;
            newColumn = column + j;

            if(newRow >= 0 && newRow < HEIGHT && newColumn >= 0 && newColumn < WIDTH && (!(i == 0 && j == 0))){
                if(board[newRow][newColumn].current == GEN1){
                    gen1Counter++;
                }
                else if(board[newRow][newColumn].current == GEN2){
                    gen2Counter++;
                }
                else if(board[newRow][newColumn].current == ZOMBIE){
                    zombieCounter++;
                }
            }
        }
    }
    *gen1Neighbors = gen1Counter;
    *gen2Neighbors = gen2Counter;
    *zombieNeighbors = zombieCounter;
}

/**
 * @brief Updates the state of each cell in the board based on the rules of the game.
 *
 * This function iterates through each cell of the board, calculates the number of alive 
 * neighbors for each cell using the countNeighbors function, and updates the state of 
 * each cell based on the rules of the game. Each cell can be in one of several states: DEAD, GEN1, 
 * GEN2, ZOMBIE, LAND, ZLAND, or PIT. The rules dictate how cells transition between these states.
 *
 * input: board the two-dimensional array representing the game board.
 * 
 */
void updateBoard(struct cell board[HEIGHT][WIDTH]){
    int i;
    int j;
    srand(time(NULL));

    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            int gen1Neighbors = 0;
            int gen2Neighbors = 0;
            int zombieNeighbors = 0;
            int spawnChance = 1;
            int totalNeighbors = 0;
            
            countNeighbors(board, i, j, &gen1Neighbors, &gen2Neighbors, &zombieNeighbors);

            totalNeighbors = gen1Neighbors + gen2Neighbors;
            
/****************************************************************************************************/
            if(board[i][j].past == PIT){
                board[i][j].future = PIT;
            }
/****************************************************************************************************/
            else if(board[i][j].current == GEN1){
                if((gen1Neighbors <= 5) && (gen1Neighbors >= totalNeighbors * 0.4)){
                    board[i][j].future = GEN1;
                }
                else if(zombieNeighbors > 2){
                    if(spawnChance == rand ()% 10){
                        board[i][j].future = ZOMBIE;
                    }
                }
                else{
                    board[i][j].future = DEAD;
                }
            }
/****************************************************************************************************/
            else if(board[i][j].current == GEN2){
                if((totalNeighbors >= 3 && totalNeighbors <= 5)){
                    if(spawnChance == rand ()% 2){
                        board[i][j].future = GEN1;
                    }
                    else{
                        board[i][j].future = GEN2;
                    }
                }
                else if(zombieNeighbors > 1){
                    board[i][j].future = ZOMBIE;
                }
                else{
                    board[i][j].future = DEAD;
                }
            }
/****************************************************************************************************/
            else if(board[i][j].current == ZOMBIE){
                if(gen1Neighbors > 2){
                    if(spawnChance == rand ()% 7){
                        board[i][j].future = GEN1;
                    }
                    else{
                        board[i][j].future = ZOMBIE;
                    }
                }
                else{
                    board[i][j].future = ZOMBIE;
                }
            }
/***************************************************************************************************/
            else if(board[i][j].current == DEAD){
                if(board[i][j].past == LAND || board[i][j].past == ZLAND){
                    if(board[i][j].past == LAND){
                        if(spawnChance == rand ()% 4){
                            board[i][j].future = GEN2;
                        }
                        else{
                            board[i][j].future = LAND;
                    }
                    }

                    else if(board[i][j].past == ZLAND){
                        if(spawnChance == rand ()% 4){
                            board[i][j].future = ZOMBIE;
                        }
                    }
                    else{
                        board[i][j].future = ZLAND;
                    }
                }
            }
/****************************************************************************************************/
            else if(board[i][j].current == ZLAND){
                if(spawnChance == rand ()% 2){
                    board[i][j].future = ZOMBIE;
                }
                else if(zombieNeighbors >= 2){
                    board[i][j].future = ZOMBIE;
                }
            }
/****************************************************************************************************/
            else if(board[i][j].current == LAND){
                if(gen1Neighbors >= 3 || (gen1Neighbors >= 0.8 * 5)){
                    board[i][j].future = GEN1;
                }
                else if(gen2Neighbors > 1 && gen2Neighbors <= 5){
                    if(gen1Neighbors > gen2Neighbors){
                        board[i][j].future = GEN1;
                    }                   
                    else if(gen1Neighbors <= gen2Neighbors){
                        board[i][j].future = GEN2;
                    }
                }
                else if(zombieNeighbors > 3){
                        board[i][j].future = ZOMBIE;
                }
            }
/****************************************************************************************************/
                else{
                    board[i][j].future = DEAD;
                }
            }
        }
/****************************************************************************************************/
            for(i = 0; i < HEIGHT; i++){
                for(j = 0; j < WIDTH; j++){
                    board[i][j].current = board[i][j].future;
                }
            }
}