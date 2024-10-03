/**
 * @file   template.c
 * @author   Christian Laiho
 * @date   2024-04-25
 * @version   1.0
 *
 * @brief Game of Zombie
 *
 * Detailed description of the program. This program is designed to 
 * demonstrate modern C programming practices, including structured 
 * documentation, use of constants, function prototypes, and 
 * basic program structure.
 *
 * This software is released under the GPL License.
 */

/* Includes */
#include "GameOfLife.h"

/* Main Function */
int main(void){
    struct cell board[HEIGHT][WIDTH];
    int iteration;
    int time;
    int userChoice;
    int i;
    int j;
    int middle;
    char choices[3][100] = {
        "Enter the number of iteration",
        "Give time in micro seconds",
        "Board from textfile choose 1 or random board choose 2",
    };
    int choice;
    int highlight = 0;
    WINDOW *menuwin;
    initializeBoard(board);
    initscr();
    start_color();
    curs_set(0);
    cbreak();
    noecho();

    init_pair(10, COLOR_GREEN, COLOR_BLACK);
    bkgd(COLOR_PAIR(10));
    init_pair(1, COLOR_MAGENTA, COLOR_GREEN);
    init_pair(2, COLOR_MAGENTA, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_GREEN);
    init_pair(4, COLOR_GREEN, COLOR_YELLOW);
    init_pair(5, COLOR_MAGENTA, COLOR_YELLOW);
    init_pair(6, COLOR_RED, COLOR_YELLOW);
    init_pair(7, COLOR_BLACK, COLOR_BLACK);


    menuwin = newwin(HEIGHT, WIDTH, 0, 0);
    keypad(menuwin, TRUE);
    box(menuwin, 0, 0);
    wrefresh(menuwin);
    wattron(menuwin, COLOR_PAIR(10));

    for(i = 0; i < 3; i++){
        while(1){
            werase(menuwin);
            box(menuwin, 0, 0);
            mvwprintw(menuwin, 1, (WIDTH - strlen("Game Of Zombie")) / 2, "Game Of Zombie");
            for(j = 0; j < 3; j++){
                if(j == highlight){
                    wattron(menuwin, A_REVERSE);
                }
                middle = (WIDTH - strlen(choices[j])) /2;
                mvwprintw(menuwin, j *2 +3, middle, choices[j]);
                wattroff(menuwin, A_REVERSE);
            }
            choice = wgetch(menuwin);

            switch(choice){
                case KEY_UP:
                    highlight--;
                    if(highlight == -1){
                        highlight = 0;
                    }
                    break;
                case KEY_DOWN:
                    highlight++;
                    if(highlight == 3){
                        highlight = 2;
                    }
                    break;
                default:
                    break;
            }

            if(choice == 10){
                break;
            }
        }
        switch(highlight){
            case 0:
                echo();
                mvwprintw(menuwin, 15, middle, "How many iterations? ");
                wscanw(menuwin, "%d", &iteration);
                noecho();
                break;
            case 1:
                echo();
                mvwprintw(menuwin, 15, middle, "How fast do you want to go? ");
                wscanw(menuwin, "%d", &time);
                noecho();
                break;
            case 2:
                echo();
                mvwprintw(menuwin, 15, middle, "1 or 2: ");
                wscanw(menuwin, "%d", &userChoice);
                noecho();
                break;
            default:
                break;
        }

        highlight++;

        if(highlight > 4){
            endwin();
            break;
        }
    }
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            if(board[i][j].past == LAND){
                attron(COLOR_PAIR(3));
                mvprintw(i, j, " ");
                attroff(COLOR_PAIR(3));
            }
            else if(board[i][j].past == ZLAND){
                attron(COLOR_PAIR(4));
                mvprintw(i, j, " ");
                attroff(COLOR_PAIR(4));
            }
            else if(board[i][j].past == PIT){
                attron(COLOR_PAIR(7));
                mvprintw(i, j, " ");
                attroff(COLOR_PAIR(7));
            }
        }
    }
    refresh();

    startConfig(board, userChoice);

    for(i = 0; i < iteration; i++){
        printBoard(board);
        updateBoard(board);
        usleep(time);
    }
    endwin();
    return 0;
}

/**
 * @brief License Information
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
