#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <fstream>
#include <random>
#include <string>

typedef struct {
  int** field;    /**< Поле игровое */
  int** next;     /**< Поле для фигуры */
  int score;      /**< Счет*/
  int high_score; /**< Общий счет*/
  int level;      /**< Уровень*/
  int speed;      /**< Скорость*/
  int pause;      /**< Пауза*/
} GameInfo_tt;

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

void start_screen(int a);
void output_tetris(GameInfo_tt game_data);
void free_data(GameInfo_tt* game_data);
void write_1(GameInfo_tt* g, int y, int x);
int check_down_coord(GameInfo_tt* g, int y, int x);
void write_0(GameInfo_tt* g, int y, int x);
void spin(int* x, int* y);
void spin_figure(position_f* figure, part_coordinate* coordinate);
void coordinate_figure(int number_figure, part_coordinate* A);
void put_figure(position_f* data_figure);
void starting_position(GameInfo_tt* game_data);
int spawn(GameInfo_tt* data_tetris);
int move_figure(GameInfo_tt* g, position_f* f, part_coordinate* c, int ch);
int delete_line(GameInfo_tt* M);
void count_score_lvl_speed(int line, GameInfo_tt* g, int* speed);
int lose_or_continue(GameInfo_tt* g);
int user_input(GameInfo_tt* g, position_f* f, part_coordinate* c, int* speed);

int lose_or_continue1(GameInfo_tt* g);
int makeRandfigure();
void count_score_lvl_speed1(int line, GameInfo_tt* g, int* speed);
int user_input1(GameInfo_tt* g, position_f* f, part_coordinate* c, int* speed);
