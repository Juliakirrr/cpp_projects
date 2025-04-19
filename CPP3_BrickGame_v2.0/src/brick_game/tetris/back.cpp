#include "../../gui/cli/tetris/main.h"
// #include <unistd.h>

void spin(int* x, int* y) {  // подфункция для spin_figure для поворотов которую
                             // я с блокнота сделалаль
  int a = (*x);
  if ((*x) == 0 || (*y) == 0) {  // если какая то равна 0
    if ((*y) != 0) {
      (*y) = (*y) * -1;
    }
    (*x) = (*y);
    (*y) = a;
  } else if ((*y) == 1 && (*x) == 1) {
    (*x) = (*x) * -1;
  } else if ((*y) == 1 && (*x) == -1) {
    (*y) = (*y) * -1;
  } else if ((*y) == -1 && (*x) == -1) {
    (*x) = (*x) * -1;
  } else if ((*y) == -1 && (*x) == 1) {
    (*y) = (*y) * -1;
  }
}

void coordinate_figure(
    int number_figure,
    part_coordinate* A) {  // координаты в зависимости от фигуры
  if (number_figure == 1) {
    A->X1 = -1, A->Y1 = 0, A->X2 = 1, A->Y2 = 0, A->X3 = 2, A->Y3 = 0;
  } else if (number_figure == 2) {
    A->X1 = 1, A->Y1 = 0, A->X2 = -1, A->Y2 = 0, A->X3 = -1, A->Y3 = -1;
  } else if (number_figure == 3) {
    A->X1 = -1, A->Y1 = 0, A->X2 = 1, A->Y2 = 0, A->X3 = 1, A->Y3 = -1;
  } else if (number_figure == 4) {
    A->X1 = 0, A->Y1 = -1, A->X2 = 1, A->Y2 = 0, A->X3 = 1, A->Y3 = -1;
  } else if (number_figure == 5) {
    A->X1 = -1, A->Y1 = 0, A->X2 = 0, A->Y2 = -1, A->X3 = 1, A->Y3 = -1;
  } else if (number_figure == 6) {
    A->X1 = -1, A->Y1 = 0, A->X2 = 0, A->Y2 = -1, A->X3 = 1, A->Y3 = 0;
  } else if (number_figure == 7) {
    A->X1 = -1, A->Y1 = -1, A->X2 = 0, A->Y2 = -1, A->X3 = 1, A->Y3 = 0;
  }
}

void starting_position(GameInfo_tt* game_data) {  // стартовые позиции

  game_data->pause = 0;

  game_data->field = (int**)calloc(20, sizeof(int*));

  for (int i = 0; i < 20; ++i) {
    game_data->field[i] = (int*)calloc(10, sizeof(int));
  }

  game_data->next = (int**)calloc(2, sizeof(int*));
  for (int i = 0; i < 2; ++i) {
    game_data->next[i] = (int*)calloc(5, sizeof(int));
  }

  game_data->speed = 100;

  game_data->level = 1;
  game_data->speed = 1;
  game_data->score = 0;
  game_data->high_score = 0;

  FILE* file = fopen("../game_score/higt_score.txt", "r");

  char buffer[15] = {};
  fgets(buffer, sizeof(buffer), file);

  int a = 1;
  for (int i = 15; i > -1; i--) {
    if (buffer[i] < 58 && buffer[i] > 47) {
      game_data->high_score = game_data->high_score + (buffer[i] - 48) * a;
      a = a * 10;
    }
  }
  fclose(file);
}

int lose_or_continue(GameInfo_tt* g) {
  // если по счету дохуя надо преезаписать в общий счет
  int error = 0;
  for (int i = 0; i < 10; i++) {
    if (g->field[0][i] == 1) {
      std::ofstream file("../game_score/higt_score.txt", std::ios::trunc);
      file << g->score;
      file.close();
      error = 1;
      break;
    }
  }
  return error;
}

int makeRandfigure() {
  std::random_device rd;  // Получаем случайное число от устройства
  std::mt19937 gen(
      rd());  // Инициализируем генератор с помощью случайного числа

  // Определяем диапазон случайных чисел
  std::uniform_int_distribution<> distrib(1, 7);

  // Генерируем случайное число
  return distrib(gen);
}

int lose_or_continue1(GameInfo_tt* g) {
  // если по счету дохуя надо преезаписать в общий счет
  int error = 0;
  for (int i = 0; i < 10; i++) {
    if (g->field[0][i] == 1) {
      std::ofstream file("../game_score/higt_score.txt", std::ios::trunc);
      file << g->score;
      file.close();
      error = 1;
      break;
    }
  }
  return error;
}

int spawn(GameInfo_tt* data_tetris) {  // циферки запись для некс
  int random_number = 1 + rand() % (7);
  part_coordinate for_next;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      data_tetris->next[i][j] = 0;
    }
  }
  coordinate_figure(random_number, &for_next);

  data_tetris->next[1][1] = 1;
  data_tetris->next[1 + for_next.Y1][1 + for_next.X1] = 1;
  data_tetris->next[1 + for_next.Y2][1 + for_next.X2] = 1;
  data_tetris->next[1 + for_next.Y3][1 + for_next.X3] = 1;
  data_tetris->next[1][4] = random_number;

  return random_number;
}

void put_figure(position_f* data_figure) {
  data_figure->Y = -1;
  data_figure->X = 4;
}

void spin_figure(position_f* figure,
                 part_coordinate* c) {  // смена координат при повороте
  if (figure->figure != 4) {
    spin(&c->X1, &c->Y1);
    spin(&c->X2, &c->Y2);
    spin(&c->X3, &c->Y3);
  }
}

void write_1(GameInfo_tt* g, int y,
             int x) {  // чекаем координаты на всякий если все ок пишем 1
  if (y > -1 && x > -1) {
    g->field[y][x] = 1;
  }
}

void write_0(GameInfo_tt* g, int y,
             int x) {  // чекаем координаты на всякий если все ок пишем 0
  if (y > -1 && x > -1) {
    g->field[y][x] = 0;
  }
}

int delete_line(GameInfo_tt* M) {
  int line = 0;
  int quantity = 0;
  int forI = -1;
  for (int i = 19; i > forI; i--) {  // до верха или до фул пустой строки
    for (int j = 0; j < 10; j++) {
      if (M->field[i][j] == 1) {
        line++;
      }
    }
    if (line == 10) {
      quantity++;
    } else if (line < 10 &&
               i != 19) {  // строка меньше ее надо сдвинуть  && i != 19
      for (int j = 0; j < 10; j++) {
        M->field[i + quantity][j] = M->field[i][j];
      }
    }
    // if(line == 0){
    //     forI = forI + quantity;
    // }
    line = 0;
  }
  return quantity;
}

int check_down_coord(GameInfo_tt* g, int y, int x) {
  int error = 0;
  if (y == 20 || (y > -1 && g->field[y][x] == 1) || x == -1 || x == 10) {
    error = 1;
  }
  return error;
}

void free_data(GameInfo_tt* game_data) {
  for (int i = 0; i < 20; ++i) {
    free(game_data->field[i]);
  }
  free(game_data->field);

  for (int i = 0; i < 2; ++i) {
    free(game_data->next[i]);
  }
  free(game_data->next);
}

void count_score_lvl_speed(int line, GameInfo_tt* g, int* speed) {
  if (line == 1) {
    g->score = g->score + 100;
  } else if (line == 2) {
    g->score = g->score + 300;
  } else if (line == 3) {
    g->score = g->score + 700;
  } else if (line == 4) {
    g->score = g->score + 1500;
  }
  if (g->score > g->high_score) {
    g->high_score = g->score;
  }

  if (((g->score / 600) + 1 > g->level) && g->level != 10) {
    g->level = g->level + 1;
    (*speed) = (*speed) - 9000;
    g->speed = g->speed + 100;
  }
}

void count_score_lvl_speed1(int line, GameInfo_tt* g, int* speed) {
  if (line == 1) {
    g->score = g->score + 100;
  } else if (line == 2) {
    g->score = g->score + 300;
  } else if (line == 3) {
    g->score = g->score + 700;
  } else if (line == 4) {
    g->score = g->score + 1500;
  }
  if (g->score > g->high_score) {
    g->high_score = g->score;
  }

  if (((g->score / 600) + 1 > g->level) && g->level != 10) {
    g->level = g->level + 1;
    (*speed) = (*speed) - 90;
    g->speed = g->speed + 100;
  }
}

int move_figure(GameInfo_tt* g, position_f* f, part_coordinate* c, int ch) {
  int a = 0, error = 0, y = 0, x = 0;
  part_coordinate test = (*c);
  // проверить не выше ли поля   // если на поле поставить 0
  write_0(g, f->Y, f->X);
  write_0(g, f->Y + c->Y1, f->X + c->X1);
  write_0(g, f->Y + c->Y2, f->X + c->X2);
  write_0(g, f->Y + c->Y3, f->X + c->X3);
  if (ch == 261) {  // right
    x = 1;
  } else if (ch == 260) {  // left
    x = -1;
  } else if (ch == 258) {  //  down
    y = 1;
  } else if (ch == 'c') {  //  spin
    spin_figure(f, c);
  }

  // проверить все ниже свободны ли они
  a = a + check_down_coord(g, f->Y + y, f->X + x);
  a = a + check_down_coord(g, f->Y + c->Y1 + y, f->X + c->X1 + x);
  a = a + check_down_coord(g, f->Y + c->Y2 + y, f->X + c->X2 + x);
  a = a + check_down_coord(g, f->Y + c->Y3 + y, f->X + c->X3 + x);

  if (a == 0) {  // ошибки нет рисуем на новом месте  прибавив к основной
                 // координате 1
    f->Y = f->Y + y;
    f->X = f->X + x;
    write_1(g, f->Y, f->X);
    write_1(g, f->Y + c->Y1, f->X + c->X1);
    write_1(g, f->Y + c->Y2, f->X + c->X2);
    write_1(g, f->Y + c->Y3, f->X + c->X3);
  } else {  // есть ошибка рисуем на старом и ошибку выдаем
    (*c) = test;
    write_1(g, f->Y, f->X);
    write_1(g, f->Y + c->Y1, f->X + c->X1);
    write_1(g, f->Y + c->Y2, f->X + c->X2);
    write_1(g, f->Y + c->Y3, f->X + c->X3);
    error = 1;
  }
  return error;
  // если на поле поставить 0
  // проверить все ниже свободны ли они
  // если сыободны рисуем на новом месте прибавив к основной координате 1 если
  // заняты рисуем на старом и ошибку выдаем
}

int user_input(GameInfo_tt* g, position_f* f, part_coordinate* c, int* speed) {
  int error = 0, a = 0;
  for (int i = 0; i < 10; i++) {
    int ch = getch();  // Ожидание нажатия любой клавиши для выхода

    move_figure(g, f, c, ch);
    if (ch == 'x') {
      g->pause = 1;
      nodelay(stdscr, FALSE);  // стопаем инкерсес
      while (a != 'x') {
        clear();
        output_tetris((*g));
        a = getch();
      }
      nodelay(stdscr, TRUE);  // возобновляем
      g->pause = 0;
    } else if (ch == 258) {
      int b = 0;
      while (b == 0) {
        b = move_figure(g, f, c, 258);
      }
    } else if (ch == 27) {
      error = 1;
      i = 10;
    }
    clear();
    output_tetris((*g));
    usleep((*speed));
  }
  return error;
}
