#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "tLib.h"
#include <time.h>


//enum direction{left, right, up, down};

WINDOW *createBoard(){ //function to create game board
    int height = 40;
    int width = 80;
    int startY = (LINES - height) / 2;
    int startX = (COLS - width) / 2;
    int score = 0;
    refresh();
    WINDOW *gameBoard;
    gameBoard = newwin(height, width, startY, startX);
    box(gameBoard, 0, 0);
    refresh();
    return(gameBoard);

}

WINDOW *updateBoard(WINDOW *gameBoard, struct bike *bikes, int score){
    char dirChars[] = {'<', '>', '^', 'V'};
    int height = 40;
    int width = 80;
    char ch;
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    
    switch(bikes[0].heading){
        case right:
            if(bikes[0].cornerFlag == uLeft){
                mvwaddch(gameBoard,bikes[0].yPos, bikes[0].xPos - 1,  ACS_ULCORNER);
                break;
                }
            if(bikes[0].cornerFlag == lLeft){
                mvwaddch(gameBoard,bikes[0].yPos, bikes[0].xPos - 1,  ACS_LLCORNER);
                break;
            }
            mvwaddch(gameBoard,bikes[0].yPos, bikes[0].xPos - 1,  ACS_HLINE);
            break;
        case left:
            if(bikes[0].cornerFlag == uRight){
                mvwaddch(gameBoard,bikes[0].yPos, bikes[0].xPos + 1,  ACS_URCORNER);
                break;
                }
            if(bikes[0].cornerFlag == lRight){
                mvwaddch(gameBoard,bikes[0].yPos, bikes[0].xPos + 1,  ACS_LRCORNER);
                break;
            }
            mvwaddch(gameBoard,bikes[0].yPos, bikes[0].xPos + 1,  ACS_HLINE);
            break;
        case up:
            if(bikes[0].cornerFlag == lLeft){
                mvwaddch(gameBoard,bikes[0].yPos + 1, bikes[0].xPos,  ACS_LLCORNER);
                break;
                }
            if(bikes[0].cornerFlag == lRight){
                mvwaddch(gameBoard,bikes[0].yPos + 1, bikes[0].xPos,  ACS_LRCORNER);
                break;
            }
            mvwaddch(gameBoard,bikes[0].yPos + 1, bikes[0].xPos,  ACS_VLINE);
            break;
        case down:
            if(bikes[0].cornerFlag == uLeft){
                mvwaddch(gameBoard,bikes[0].yPos - 1, bikes[0].xPos,  ACS_ULCORNER);
                break;
                }
            if(bikes[0].cornerFlag == uRight){
                mvwaddch(gameBoard,bikes[0].yPos - 1, bikes[0].xPos,  ACS_URCORNER);
                break;
            }
            mvwaddch(gameBoard,bikes[0].yPos - 1, bikes[0].xPos,  ACS_VLINE);
            break;
    }
    
    mvwaddch(gameBoard, bikes[0].yPos, bikes[0].xPos, dirChars[bikes[0].heading]);

    switch(bikes[1].heading){
        case right:
            if(bikes[1].cornerFlag == uLeft){
                mvwaddch(gameBoard,bikes[1].yPos, bikes[1].xPos - 1,  ACS_ULCORNER);
                break;
                }
            if(bikes[1].cornerFlag == lLeft){
                mvwaddch(gameBoard,bikes[1].yPos, bikes[1].xPos - 1,  ACS_LLCORNER);
                break;
            }
            mvwaddch(gameBoard,bikes[1].yPos, bikes[1].xPos - 1,  ACS_HLINE);
            break;
        case left:
            if(bikes[1].cornerFlag == uRight){
                mvwaddch(gameBoard,bikes[1].yPos, bikes[1].xPos + 1,  ACS_URCORNER);
                break;
                }
            if(bikes[1].cornerFlag == lRight){
                mvwaddch(gameBoard,bikes[1].yPos, bikes[1].xPos + 1,  ACS_LRCORNER);
                break;
            }
            mvwaddch(gameBoard,bikes[1].yPos, bikes[1].xPos + 1,  ACS_HLINE);
            break;
        case up:
            if(bikes[1].cornerFlag == lLeft){
                mvwaddch(gameBoard,bikes[1].yPos + 1, bikes[1].xPos,  ACS_LLCORNER);
                break;
                }
            if(bikes[1].cornerFlag == lRight){
                mvwaddch(gameBoard,bikes[1].yPos + 1, bikes[1].xPos,  ACS_LRCORNER);
                break;
            }
            mvwaddch(gameBoard,bikes[1].yPos + 1, bikes[1].xPos,  ACS_VLINE);
            break;
        case down:
            if(bikes[1].cornerFlag == uLeft){
                mvwaddch(gameBoard,bikes[1].yPos - 1, bikes[1].xPos,  ACS_ULCORNER);
                break;
                }
            if(bikes[1].cornerFlag == uRight){
                mvwaddch(gameBoard,bikes[1].yPos - 1, bikes[1].xPos,  ACS_URCORNER);
                break;
            }
            mvwaddch(gameBoard,bikes[1].yPos - 1, bikes[1].xPos,  ACS_VLINE);
            break;
    }
    mvwaddch(gameBoard, bikes[1].yPos, bikes[1].xPos, dirChars[bikes[1].heading]);
  //  wmove(gameBoard, 100,100);
    wrefresh(gameBoard);
    return(gameBoard);
}

void gameOver(WINDOW *gameBoard){
    clear();
    int startY = (LINES) / 2;
    int startX = ((COLS) / 2) - 6;
    start_color();
    mvprintw(startY, startX, "GAME OVER");
    refresh();
}


struct bike bikeLogic(struct bike bike, WINDOW* gameBoard){
    char ch;
    switch(bike.heading){
        case right:  
            bike.xPos++;
            break;
            
        case left:
            bike.xPos--;
            break;
        case up:
            bike.yPos--;
            break;
        case down:
            bike.yPos++;
            break;
        default:
            break;
    }
    return bike;
}

struct bike p2Input(struct bike bike, WINDOW* gameBoard){
    char inChar;
    enum direction retDir = bike.heading;
    bike.cornerFlag = none;
    int random = rand() % 3;
    if(bike.xPos < 5 || bike.xPos > 70)random = rand() % 3;
    if(bike.yPos < 3 || bike.yPos > 30)random = rand() % 3;

        switch(random){
            case 0:
                if(retDir == right)break;
                else if(retDir == up)bike.cornerFlag = uRight;
                else if(retDir == down)bike.cornerFlag = lRight;
                retDir = left;
                break;
                
            case 1:
                if(retDir == left)break;
                else if(retDir == up)bike.cornerFlag = uLeft;
                else if(retDir == down)bike.cornerFlag =lLeft;
                retDir = right;
                break;
            case 2:
                if(retDir == down)break;
                else if(retDir == left)bike.cornerFlag = lLeft;
                else if(retDir == right)bike.cornerFlag = lRight;
                retDir = up;
                break;
            case 3:
                if(retDir == up)break;
                else if(retDir == left)bike.cornerFlag = uLeft;
                else if(retDir == right)bike.cornerFlag = uRight;
                retDir = down;
                break;
        }
    bike.heading = retDir;   
    return(bike);
}


struct bike input(struct bike bike, WINDOW* gameBoard){
    char inChar;
    enum direction retDir = bike.heading;
    bike.cornerFlag = none;
        switch(wgetch(gameBoard)){
            case 'a':
                if(retDir == right)break;
                else if(retDir == up)bike.cornerFlag = uRight;
                else if(retDir == down)bike.cornerFlag = lRight;
                retDir = left;
                break;
                
            case 'd':
                if(retDir == left)break;
                else if(retDir == up)bike.cornerFlag = uLeft;
                else if(retDir == down)bike.cornerFlag =lLeft;
                retDir = right;
                break;
            case 'w':
                if(retDir == down)break;
                else if(retDir == left)bike.cornerFlag = lLeft;
                else if(retDir == right)bike.cornerFlag = lRight;
                retDir = up;
                break;
            case 's':
                if(retDir == up)break;
                else if(retDir == left)bike.cornerFlag = uLeft;
                else if(retDir == right)bike.cornerFlag = uRight;
                retDir = down;
                break;
            default:
                break;
        }
    bike.heading = retDir;  
    return(bike);
}