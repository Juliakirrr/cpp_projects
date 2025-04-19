#ifndef TETRIS_H
#define TETRIS_H

#include <QTimer>
#include <QWidget>

#include "../../cli/tetris/main.h"
#include "ui_tetris.h"

namespace Ui {
class tetris;
}

class tetris : public QWidget {
  Q_OBJECT

 public:
  explicit tetris(QWidget *parent = nullptr);
  ~tetris();

 protected:
  void keyPressEvent(QKeyEvent *event) override;  // Обработка нажатий клавиш

 private slots:
  void updateGame();  // Слот для обновления игры

 private:
  Ui::tetris *ui;
  GameInfo_tt data;
  position_f figure;
  part_coordinate coordinate;
  int endgame;
  int speedGame;
  QTimer *gameTimer;

  void updateTableWidget();  // Обновление интерфейса
  void updateWidget(QTableWidget *tableWidget,
                    const GameInfo_tt &data);  // Обновление виджета
  void updateWidget2(QTableWidget *tableWidget,
                     const GameInfo_tt &data);  // Обновление виджета
  void startNewGame();  // Начало новой игры
  void PutGameInfo_tt();
  void ClearGameInfo_tt();
};

#endif  // TETRIS_H
