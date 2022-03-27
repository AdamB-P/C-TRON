#include <stdlib.h>
#include <stdio.h>
#include "tLib.h"
#include <ncurses.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int count;
    int height = 40;
    int width = 80;
    int numBikes = 2;
    int gameOverFlag = 0;
    int score = 0;
    char fullSpaces[height][width];
    struct bike bikeArray[numBikes]; 
    char dirChars[] = {'<', '>', '^', 'V'};
    initscr();
    refresh();
    curs_set(0);
    bikeArray[0].xPos = width / 4;
    bikeArray[0].yPos = height / 2;
    bikeArray[0].heading = right;

    bikeArray[1].xPos = (width / 4) + (width / 2);
    bikeArray[1].yPos = height / 2;
    bikeArray[1].heading = left;
    noecho();
    WINDOW* gameBoard = createBoard();
    nodelay(gameBoard, true);
    gameBoard = updateBoard(gameBoard, bikeArray, score);

    wrefresh(gameBoard);
    
    while(gameOverFlag == 0){
        usleep(50000); 
        int cFlag = 0;
        bikeArray[0] = input(bikeArray[0], gameBoard);
        bikeArray[1] = p2Input(bikeArray[1], gameBoard);

        bikeArray[0] = bikeLogic(bikeArray[0], gameBoard);
        bikeArray[1] = bikeLogic(bikeArray[1], gameBoard);
       if(fullSpaces[bikeArray[0].yPos][bikeArray[0].xPos] == 'f' || fullSpaces[bikeArray[1].yPos][bikeArray[1].xPos] == 'f' || bikeArray[0].xPos > 79 || bikeArray[0].xPos <1 || bikeArray[0].yPos >39 || bikeArray[0].yPos <1 || bikeArray[1].xPos > 79 || bikeArray[1].xPos <1 || bikeArray[1].yPos >39 || bikeArray[1].yPos <1){
           gameOver(gameBoard);
            break;
       }
       fullSpaces[bikeArray[0].yPos][bikeArray[0].xPos] = 'f';
       fullSpaces[bikeArray[1].yPos][bikeArray[1].xPos] = 'f';
        if(bikeArray[0].gameOver == 1 || bikeArray[1].gameOver == 1){
            gameOver(gameBoard);
            break;
        } 
        gameBoard = updateBoard(gameBoard, bikeArray, score);
        
        
        wrefresh(gameBoard);

    }


    getch();
    endwin();

}

