#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "snakeD.h"
#include "tetris.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class mainwindow;
}
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
  Q_OBJECT

 public:
  mainwindow(QWidget *parent = nullptr);
  ~mainwindow();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::mainwindow *ui;
};
#endif  // MAINWINDOW_H
