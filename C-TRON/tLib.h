#ifndef TLIB
#define TLIB
#include <ncurses.h>

enum direction{left, right, up, down};
enum flag{uRight, uLeft, lRight, lLeft, none};

struct bike{
    int xPos;
    int yPos;
    int bikeId;
    int gameOver;
    enum flag cornerFlag;
    enum direction heading;

};

WINDOW *createBoard();

WINDOW *updateBoard(WINDOW *gameBoard, struct bike *bikes, int score);

struct bike p2Input(struct bike bike, WINDOW* gameBoard);

void gameOver(WINDOW *gameBoard);

struct bike bikeLogic(struct bike bike, WINDOW* gameBoard);

struct bike input(struct bike bike, WINDOW *gameBoard);
#endif //TLIB

