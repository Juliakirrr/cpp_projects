#ifndef GUI_SNAKE
#define GUI_SNAKE

#include <ncurses.h>

#include "../../../brick_game/snake/snake.h"

void PrintInfo(int i, GameInfo_t data);
void printStart(GameInfo_t data);
void printGame(GameInfo_t data);
void GameS();
void PrintLoss(GameInfo_t data);
void PrintWin(GameInfo_t data);
void InitNcurses();
void PrintPause(GameInfo_t data);
void printField(GameInfo_t data);
UserAction_t UserInputButton(int ch);

#endif