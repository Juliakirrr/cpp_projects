#include "snakeD.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>

#include "ui_snakeD.h"

snake::snake(QWidget *parent) : QWidget(parent), ui(new Ui::snake) {
  ui->setupUi(this);
  setWindowTitle("Snake");

  userInput(Start, false);
  updateGame();

  // Таймер для обновления игры
  gameTimer = new QTimer(this);
  connect(gameTimer, &QTimer::timeout, this, &snake::updateGameS);
  gameTimer->start(5);
}

snake::~snake() { delete ui; }

void snake::updateGameS() {
  userInput(NoAction, false);
  updateGame();  // Обновляем состояние игры

  if (GetGameController()->state == Loss_ ||
      GetGameController()->state == Win_) {
    gameTimer->stop();  // Останавливаем таймер, если игра завершена
    QMessageBox::information(this, "Game Over", "Игра завершена!");
    return;
  }
  printField(updateCurrentState());  // Обновляем интерфейс
}

void snake::printField(GameInfo_t data) {
  updateWidget(ui->tableWidget, data);

  ui->label_11->setText(QString::number(data.level));
  ui->label_11->setStyleSheet("QLabel { font-size: 50px; }");
  ui->label_9->setText(QString::number(data.speed));
  ui->label_9->setStyleSheet("QLabel { font-size: 50px; }");
  ui->label_6->setText(QString::number(data.score));
  ui->label_6->setStyleSheet("QLabel { font-size: 50px; }");
  ui->label_2->setText(QString::number(data.high_score));
  ui->label_2->setStyleSheet("QLabel { font-size: 50px; }");

  // if (data.pause == 1) {
  //     QMessageBox::information(this, "Пауза", "Игра на паузе. Нажмите P,
  //     чтобы продолжить.");
  // }
}

void snake::updateWidget(QTableWidget *tableWidget, const GameInfo_t data) {
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 10; ++j) {
      QTableWidgetItem *item = tableWidget->item(i, j);
      if (!item) {
        item = new QTableWidgetItem();
        tableWidget->setItem(i, j, item);
      }
      if (data.field[i][j] == 0) {
        item->setBackground(Qt::black);

      } else if (data.field[i][j] == 3) {
        item->setBackground(Qt::darkRed);  // Иначе установить черный цвет

      } else if (data.field[i][j] == 2) {
        item->setBackground(Qt::darkGray);  // Иначе установить черный цвет
      } else {
        item->setBackground(Qt::gray);  // Иначе установить черный цвет
      }
    }
  }
}

void snake::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Up:
      userInput(Up, false);
      break;
    case Qt::Key_Down:
      userInput(Down, false);
      break;
    case Qt::Key_Left:
      userInput(Left, false);
      break;
    case Qt::Key_Right:
      userInput(Right, false);
      break;
    case Qt::Key_Space:
      userInput(Action, false);
      break;
    case Qt::Key_Enter:
      userInput(Start, false);
      break;
    case Qt::Key_X:
      userInput(Pause, false);
      break;
    default:
      QWidget::keyPressEvent(event);
  }
  updateGame();
  printField(updateCurrentState());
}
