#include "front.h"

using namespace s21;

void PrintWin(GameInfo_t data) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 11; j++) {
      if (j < 10) {
        if (i == 6 && j == 0) {
          attron(COLOR_PAIR(6));
          printw("       VICTORY      ");
          attroff(COLOR_PAIR(6));

        } else if (i == 10 && j == 0) {
          attron(COLOR_PAIR(6));
          printw("   click on enter   ");
          attroff(COLOR_PAIR(6));
        } else if (i == 11 && j == 0) {
          attron(COLOR_PAIR(6));
          printw("       to exit      ");
          attroff(COLOR_PAIR(6));
        } else if (i != 6 && i != 10 && i != 11) {
          attron(COLOR_PAIR(4));
          printw("  ");
          attroff(COLOR_PAIR(4));
        }
      } else {
        PrintInfo(i, data);
      }
    }
    printw("\n");
  }
}

void PrintLoss(GameInfo_t data) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 11; j++) {
      if (j < 10) {
        if (i == 6 && j == 0) {
          attron(COLOR_PAIR(6));
          printw("        LOSS        ");
          attroff(COLOR_PAIR(6));
        } else if (i == 10 && j == 0) {
          attron(COLOR_PAIR(6));
          printw("   click on enter   ");
          attroff(COLOR_PAIR(6));
        } else if (i == 11 && j == 0) {
          attron(COLOR_PAIR(6));
          printw("       to exit      ");
          attroff(COLOR_PAIR(6));
        } else if (i != 6 && i != 10 && i != 11) {
          attron(COLOR_PAIR(4));
          printw("  ");
          attroff(COLOR_PAIR(4));
        }
      } else {
        PrintInfo(i, data);
      }
    }
    printw("\n");
  }
}

void printStart(GameInfo_t data) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 11; j++) {
      if (j < 10) {
        if (i == 9 && j == 0) {
          attron(COLOR_PAIR(6));
          printw("    press enter     ");
          attroff(COLOR_PAIR(6));
        } else if (i == 10 && j == 0) {
          attron(COLOR_PAIR(6));
          printw("    for start       ");
          attroff(COLOR_PAIR(6));

        } else if (i != 10 && i != 9) {
          attron(COLOR_PAIR(4));
          printw("  ");
          attroff(COLOR_PAIR(4));
        }
      } else {
        PrintInfo(i, data);
      }
    }
    printw("\n");
  }
}

void printGame(GameInfo_t data) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 11; j++) {
      if (j < 10) {
        if (data.field[i][j] == 0) {
          attron(COLOR_PAIR(4));
          printw("  ");
          attroff(COLOR_PAIR(4));
        } else if (data.field[i][j] == 3) {  // apple
          attron(COLOR_PAIR(1));
          printw("  ");
          attroff(COLOR_PAIR(1));
        } else if (data.field[i][j] == 2) {
          attron(COLOR_PAIR(2));
          printw("  ");
          attroff(COLOR_PAIR(2));
        } else {
          attron(COLOR_PAIR(7));
          printw("  ");
          attroff(COLOR_PAIR(7));
        }
      } else {
        PrintInfo(i, data);
      }
    }
    printw("\n");
  }
}

void PrintInfo(int i, GameInfo_t data) {
  if (i == 2) {
    printw("   Score:");
  } else if (i == 3) {
    printw("     %d", data.score);
  } else if (i == 7) {
    printw("   High score:");
  } else if (i == 8) {
    printw("     %d", data.high_score);
  } else if (i == 12) {
    printw("   Level:");
  } else if (i == 13) {
    printw("     %d", data.level);
  } else if (i == 17) {
    printw("   Speed:");
  } else if (i == 18) {
    printw("     %d", data.speed);
  }
}

void PrintPause(GameInfo_t data) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 11; j++) {
      if (j < 10) {
        if (i == 9 && j == 0) {
          attron(COLOR_PAIR(6));
          printw("       Pause        ");
          attroff(COLOR_PAIR(6));

        } else if (i != 9) {
          attron(COLOR_PAIR(4));
          printw("  ");
          attroff(COLOR_PAIR(4));
        }
      } else {
        PrintInfo(i, data);
      }
    }
    printw("\n");
  }
}

void printField(GameInfo_t data) {  // печатаем поле
  erase();
  Controller* controller = GetGameController();
  if (controller->state == Start_) {
    printStart(data);

  } else if (controller->state == Game_) {
    printGame(data);

  } else if (controller->state == Pause_) {
    PrintPause(data);

  } else if (controller->state == Win_) {
    PrintWin(data);

  } else if (controller->state == Loss_) {
    PrintLoss(data);
  }
}
//
void InitNcurses() {
  initscr();
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);
  start_color();

  init_pair(1, COLOR_RED, COLOR_RED);  // Красный текст на черном фоне
  init_pair(2, COLOR_GREEN, COLOR_BLUE);  // Зеленый текст на черном фоне
  init_pair(3, COLOR_BLUE, COLOR_BLACK);  // Синий текст на черном фоне
  init_pair(4, COLOR_BLUE, COLOR_WHITE);  // Синий текст на черном фоне
  init_pair(5, COLOR_BLUE, COLOR_MAGENTA);  // Синий текст на черном фоне
  init_pair(6, COLOR_BLACK, COLOR_YELLOW);  // Синий текст на черном фоне
  init_pair(7, COLOR_WHITE, COLOR_CYAN);  // Синий текст на черном фоне
  init_pair(8, COLOR_WHITE, COLOR_GREEN);  // Синий текст на черном фоне
}

UserAction_t UserInputButton(int ch) {
  UserAction_t button;
  if (ch == 'x') {
    button = Pause;
  } else if (ch == 27) {  // Код клавиши Escape
    button = Terminate;
  } else if (ch == 10) {  // Код клавиши Enter
    button = Start;
  } else if (ch == KEY_UP) {
    button = Up;
  } else if (ch == KEY_DOWN) {
    button = Down;
  } else if (ch == KEY_LEFT) {
    button = Left;
  } else if (ch == KEY_RIGHT) {
    button = Right;
  } else if (ch == ' ') {
    button = Action;
  } else {
    button = NoAction;
  }
  return button;
}

void GameS() {
  InitNcurses();
  bool end = true;
  while (end) {
    timeout(5);
    userInput(UserInputButton(getch()), 0);
    end = updateGame();
    printField(updateCurrentState());
  }

  endwin();
}

int main() {
  GameS();
  return 0;
}