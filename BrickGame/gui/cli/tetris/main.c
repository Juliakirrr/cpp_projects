#include "main.h"

int main() {
  // game_tetris();
  GameInfo_tt tetris;  // сделать free
  position_f figure;
  part_coordinate coordinate;
  int end = 0, speed = 90000, endgame = 0;
  starting_position(&tetris);  // постановка в стартовое положение
  initscr();                   // Инициализация ncurses
  keypad(stdscr, TRUE);  // Включение обработки специальных клавиш
  start_screen(1);  // заставка
  getch();
  clear();
  nodelay(stdscr, TRUE);  // включаем необязательный ввод
  srand(time(NULL));
  figure.figure = 1 + rand() % (7);  // узнали 1 фигурку
  while (end == 0) {
    int a = 0;
    int next = spawn(&tetris);  // узнали некст фигурку
    put_figure(&figure);  // положить главну точку фигуры
    coordinate_figure(figure.figure,
                      &coordinate);  // пишем координаты по фигуре в структуру
    while (a == 0) {
      output_tetris(tetris);
      endgame = user_input(&tetris, &figure, &coordinate, &speed);
      if (endgame == 1) {
        break;
        break;
      }
      a = move_figure(&tetris, &figure, &coordinate, 258);
      clear();
    }
    count_score_lvl_speed(delete_line(&tetris), &tetris, &speed);
    end = lose_or_continue(&tetris);
    if (endgame == 1) {
      break;
    }
    figure.figure = next;
  }
  nodelay(stdscr, FALSE);  // стопаем инкерсес
  clear();
  start_screen(2);  // заставка
  getch();
  clear();
  endwin();  // Завершение работы с ncurses
  free_data(&tetris);

  return 0;
}
