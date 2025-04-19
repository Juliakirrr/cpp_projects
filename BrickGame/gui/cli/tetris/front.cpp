#include "main.h"
// using namespace s21;

void start_screen(int a) {  // вывод заставки
  start_color();  // Инициализация цветовой схемы
  init_pair(1, COLOR_WHITE, COLOR_BLACK);  // белый текст на черном фоне
  init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);  // Зеленый текст на черном фоне
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);  // желтый2 текст на черном фоне
  init_pair(4, COLOR_YELLOW, COLOR_GREEN);  // желтый2 текст на черном фоне
  init_pair(5, COLOR_YELLOW, COLOR_CYAN);  // желтый2 текст на черном фоне
  init_pair(6, COLOR_YELLOW, COLOR_RED);  // желтый2 текст на черном фоне
  init_pair(7, COLOR_YELLOW, COLOR_BLUE);  // желтый2 текст на черном фоне

  FILE *file;  // Создаем указатель на файл
  char ch;

  // Открываем файл для чтения
  if (a == 1) {
    file = fopen("../game_score/start.txt", "r");
    if (file == NULL) {
      printf("пупупу");
    }
  } else if (a == 2) {
    file = fopen("../game_score/end.txt", "r");
    if (file == NULL) {
      printf("пупупу");
    }
  }
  if (file == NULL) {
    printf("Ошибка при открытии файла.\n");
  } else {
    // int a =0;
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '*') {
        attron(COLOR_PAIR(1));  // Установка красного текста
        printw("  ");
        attroff(COLOR_PAIR(1));  // Сброс атрибутов текста
      } else if (ch == 'y') {
        attron(COLOR_PAIR(3));  // Установка красного текста
        printw("  ");
        attroff(COLOR_PAIR(3));  // Сброс атрибутов текста
      } else if (ch == 'd') {
        attron(COLOR_PAIR(5));  // Установка красного текста
        printw("  ");
        attroff(COLOR_PAIR(5));  // Сброс атрибутов текста
      } else if (ch == 'g') {
        attron(COLOR_PAIR(4));  // Установка красного текста
        printw("  ");
        attroff(COLOR_PAIR(4));  // Сброс атрибутов текста
      } else if (ch == 'p') {
        attron(COLOR_PAIR(2));  // Установка красного текста
        printw("  ");
        attroff(COLOR_PAIR(2));  // Сброс атрибутов текста
      } else if (ch == 'r') {
        attron(COLOR_PAIR(6));  // Установка красного текста
        printw("  ");
        attroff(COLOR_PAIR(6));  // Сброс атрибутов текста
      } else if (ch == 'b' || ch == '-') {
        attron(COLOR_PAIR(7));  // Установка красного текста
        printw("  ");
        attroff(COLOR_PAIR(7));  // Сброс атрибутов текста
      } else {
        printw("%c", ch);
      }
    }
    fclose(file);
  }
}

void output_tetris(GameInfo_tt game_data) {  // вывод тетриса по структуре
  start_color();  // Инициализация цветовой схемы
  init_pair(1, COLOR_WHITE, COLOR_BLACK);  // белый текст на черном фоне
  init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);  // Зеленый текст на черном фоне
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);  // желтый2 текст на черном фоне
  init_pair(4, COLOR_YELLOW, COLOR_GREEN);  // желтый2 текст на черном фоне

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 22; j++) {
      if (j < 10 && i < 20) {
        if (game_data.pause == 0) {
          if (game_data.field[i][j] == 1) {
            attron(COLOR_PAIR(2));  // Установка красного текста
            printw("  ");
            attroff(COLOR_PAIR(2));  // Сброс атрибутов текста
          } else if (game_data.field[i][j] == 0) {
            attron(COLOR_PAIR(3));  // Установка красного текста
            printw("  ");
            attroff(COLOR_PAIR(3));  // Сброс атрибутов текста
          }
        } else if (game_data.pause == 1) {
          if (i == 10 && j == 0) {
            printw("       PAUSE        ");
          } else if (i != 10) {
            attron(COLOR_PAIR(3));  // Установка красного текста
            printw("  ");
            attroff(COLOR_PAIR(3));  // Сброс атрибутов текста
          }
        }
      } else {
        attron(COLOR_PAIR(1));
        if (i == 0 && j == 15) {
          printw("NEXT");
          break;
        }
        if (i == 2 && j == 14) {
          if (game_data.next[1][4] != 1 && game_data.next[1][4] != 4) {
            printw(" ");
          }
          for (int k = 0; k < 4; k++) {
            if (game_data.next[0][k] == 1) {
              attron(COLOR_PAIR(2));  // розовый
              printw("  ");
              attroff(COLOR_PAIR(2));  // Сброс атриб
            } else {
              attron(COLOR_PAIR(1));  // розовый
              printw("  ");
              attroff(COLOR_PAIR(1));  // Сброс атриб
            }
          }
        }
        if (i == 3 && j == 14) {
          if (game_data.next[1][4] != 1 && game_data.next[1][4] != 4) {
            printw(" ");
          }
          for (int k = 0; k < 4; k++) {
            if (game_data.next[1][k] == 1) {
              attron(COLOR_PAIR(2));  // розовый
              printw("  ");
              attroff(COLOR_PAIR(2));  // Сброс атриб
            } else {
              attron(COLOR_PAIR(1));  // розовый
              printw("  ");
              attroff(COLOR_PAIR(1));  // Сброс атриб
            }
          }
        }
        if (i == 5 && j == 15) {
          printw("LEVEL");
          break;
        }
        if (i == 6 && j == 16) {
          printw("%d", game_data.level);
          break;
        }
        if (i == 9 && j == 15) {
          printw("SPEED");
          break;
        }
        if (i == 10 && j == 16) {
          printw("%d", game_data.speed);
          break;
        }
        if (i == 13 && j == 15) {
          printw("SCORE");
          break;
        }
        if (i == 14 && j == 16) {
          printw("%d", game_data.score);
          break;
        }
        if (i == 17 && j == 14) {
          printw("HIGH SCORE");
          break;
        }
        if (i == 18 && j == 16) {
          printw("%d", game_data.high_score);
          break;
        }

        else {
          printw("  ");
        }
        attroff(COLOR_PAIR(1));
      }
    }
    printw("\n");
  }
}
