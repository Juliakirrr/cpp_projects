#ifndef GAMETETRIS_H
#define GAMETETRIS_H

#include <fstream>
#include <random>
#include <string>

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;

} GameInfo_t;

typedef struct {
  int figure; /**< Номер фигуры*/
  int X;      /**< Координата по Х*/
  int Y;      /**< Координата по У*/

} position_f;

typedef struct {
  int X1; /**< Коодинаты 1 по Х*/
  int Y1; /**< Коодинаты 1 по У*/
  int X2; /**< Коодинаты 2 по Х*/
  int Y2; /**< Коодинаты 2 по У*/
  int X3; /**< Коодинаты 3 по Х*/
  int Y3; /**< Коодинаты 3 по У*/
} part_coordinate;

int makeRandfigure();
int spawn(GameInfo_t* data_tetris);
void coordinate_figure(int number_figure, part_coordinate* A);
void put_figure(position_f* data_figure);
int move_figure(GameInfo_t* g, position_f* f, part_coordinate* c, int ch);
void write_0(GameInfo_t* g, int y, int x);
void spin_figure(position_f* figure, part_coordinate* c);
int check_down_coord(GameInfo_t* g, int y, int x);
void count_score_lvl_speed(int line, GameInfo_t* g, int* speed);
void write_1(GameInfo_t* g, int y, int x);
int delete_line(GameInfo_t* M);
void spin(int* x, int* y);
int user_input(GameInfo_t* g, position_f* f, part_coordinate* c, int* speed);
int lose_or_continue(GameInfo_t* g);

#endif  // GAMETETRIS_H
