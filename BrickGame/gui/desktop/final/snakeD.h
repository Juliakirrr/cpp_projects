#ifndef SNAKED_H
#define SNAKED_H

#include <QKeyEvent>
#include <QMessageBox>
#include <QTableWidget>
#include <QTimer>
#include <QWidget>

#include "../../../brick_game/snake/snake.h"

namespace Ui {
class snake;
}

class snake : public QWidget {
  Q_OBJECT

 public:
  explicit snake(QWidget *parent = nullptr);
  ~snake();
  void updateGameS();
  void updateWidget(QTableWidget *tableWidget, const GameInfo_t data);
  void printField(GameInfo_t data);

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 private:
  Ui::snake *ui;
  QTimer *gameTimer;
};

#endif  // SNAKED_H
