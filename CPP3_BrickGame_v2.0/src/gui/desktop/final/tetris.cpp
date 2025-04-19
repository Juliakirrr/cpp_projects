#include "tetris.h"

#include <QKeyEvent>
#include <QMessageBox>

tetris::tetris(QWidget *parent) : QWidget(parent), ui(new Ui::tetris) {
  ui->setupUi(this);
  setWindowTitle("Tetris");
  PutGameInfo_tt();

  // Настройка таблиц
  updateWidget(ui->tableWidget, data);  // Основное поле
  // Инициализация игры
  endgame = 0;
  speedGame = 1000;
  figure.figure = makeRandfigure();  // Генерация первой фигуры
  put_figure(&figure);
  coordinate_figure(figure.figure, &coordinate);
  spawn(&data);  // Генерация следующей фигуры

  // Таймер для обновления игры
  gameTimer = new QTimer(this);
  connect(gameTimer, &QTimer::timeout, this, &tetris::updateGame);
  gameTimer->start(speedGame);  // Интервал 500 мс
}

tetris::~tetris() {
  ClearGameInfo_tt();
  delete ui;
}

// Обработка нажатий клавиш
void tetris::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      if (data.pause == 0)
        move_figure(&data, &figure, &coordinate, 260);  // Влево
      break;
    case Qt::Key_Right:
      if (data.pause == 0)
        move_figure(&data, &figure, &coordinate, 261);  // Вправо
      break;
    case Qt::Key_Down:
      if (data.pause == 0)
        move_figure(&data, &figure, &coordinate, 258);  // Вниз
      break;
    case Qt::Key_Up:
      if (data.pause == 0)
        move_figure(&data, &figure, &coordinate, 'c');  // Поворот
      break;
    case Qt::Key_Space:
      if (data.pause == 0) {
        // Мгновенное падение
        while (!move_figure(&data, &figure, &coordinate, 258)) {
        }
      }
      break;
    case Qt::Key_X:                          // Обработка паузы
      data.pause = data.pause == 1 ? 0 : 1;  // Переключаем паузу
      if (data.pause == 1) {
        gameTimer->stop();  // Останавливаем таймер
      } else {
        gameTimer->start(speedGame);  // Возобновляем таймер
      }
      break;
  }

  updateTableWidget();  // Обновляем интерфейс
}

// Слот для обновления игры
void tetris::updateGame() {
  if (!endgame && data.pause == 0) {
    // Двигаем фигуру вниз
    if (move_figure(&data, &figure, &coordinate, 258)) {
      // Если фигура достигла дна
      int lines = delete_line(&data);
      count_score_lvl_speed1(lines, &data, &speedGame);
      gameTimer->setInterval(speedGame);

      // Генерация новой фигуры
      figure.figure = data.next[1][4];  // Берем следующую фигуру
      put_figure(&figure);
      coordinate_figure(figure.figure, &coordinate);

      // Генерация следующей фигуры
      spawn(&data);

      // Проверка на проигрыш
      if (lose_or_continue1(&data)) {
        endgame = 1;
        gameTimer->stop();  // Останавливаем таймер
        QMessageBox::information(this, "Game Over", "You lost!");
      }
    }

    updateTableWidget();  // Обновляем интерфейс
  }
}

// Обновление интерфейса
void tetris::updateTableWidget() {
  updateWidget(ui->tableWidget, data);  // Основное поле
  updateWidget2(ui->tableWidget_2, data);  // Поле "следующая фигура"
  // ui->label_11 = data.level;
  ui->label_11->setText(QString::number(data.level));
  ui->label_11->setStyleSheet("QLabel { font-size: 50px; }");
  ui->label_9->setText(QString::number(data.speed));
  ui->label_9->setStyleSheet("QLabel { font-size: 50px; }");
  ui->label_6->setText(QString::number(data.score));
  ui->label_6->setStyleSheet("QLabel { font-size: 50px; }");
  ui->label_2->setText(QString::number(data.high_score));
  ui->label_2->setStyleSheet("QLabel { font-size: 50px; }");

  // if (data.pause == 1) {
  //     // Отображаем сообщение о паузе
  //     QMessageBox::information(this, "Пауза", "Игра на паузе. Нажмите X,
  //     чтобы продолжить.");
  // }
}

// Обновление виджета
void tetris::updateWidget(QTableWidget *tableWidget, const GameInfo_tt &data) {
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 10; ++j) {
      QTableWidgetItem *item = tableWidget->item(i, j);
      if (!item) {
        item = new QTableWidgetItem();
        tableWidget->setItem(i, j, item);
      }
      item->setBackground(data.field[i][j] == 1 ? Qt::green : Qt::black);
    }
  }
}

void tetris::updateWidget2(QTableWidget *tableWidget, const GameInfo_tt &data) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      QTableWidgetItem *item = tableWidget->item(i, j);
      if (!item) {
        item = new QTableWidgetItem();
        tableWidget->setItem(i, j, item);
      }
      item->setBackground(data.next[i][j] == 1 ? Qt::green : Qt::black);
    }
  }
}

void tetris::PutGameInfo_tt() {  // конструктор
  data.pause = 0;

  data.field = new int *[20];
  for (int i = 0; i < 20; ++i) {
    data.field[i] = new int[10];
    for (int j = 0; j < 10; j++) {
      data.field[i][j] = 0;
    }
  }

  data.next = new int *[2];
  for (int i = 0; i < 2; ++i) {
    data.next[i] = new int[5];
    for (int j = 0; j < 5; j++) {
      data.next[i][j] = 0;
    }
  }

  data.speed = 100;

  data.level = 1;
  data.speed = 100;
  data.score = 0;
  data.high_score = 0;

  std::ifstream inputFile("../game_score/higt_score.txt");

  std::string line;
  std::getline(inputFile, line);

  int a = 1;
  for (int i = line.size() - 1; i > -1; i--) {
    if (line[i] < 58 && line[i] > 47) {
      data.high_score = data.high_score + (line[i] - 48) * a;
      a = a * 10;
    }
  }
  inputFile.close();
}

void tetris::ClearGameInfo_tt() {
  for (int i = 0; i < 20; ++i) {
    delete[] data.field[i];
  }
  delete[] data.field;

  // for(int i = 0; i < 2; )

  for (int i = 0; i < 2; ++i) {
    delete[] data.next[i];
  }
  delete[] data.next;

  std::ofstream file("../game_score/higt_score.txt", std::ios::trunc);
  file << data.score;
  file.close();
};
