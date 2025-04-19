#include "mainwindow.h"

#include "ui_mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainwindow) {
  ui->setupUi(this);
  setWindowTitle("BrickGame");
}

mainwindow::~mainwindow() { delete ui; }

void mainwindow::on_pushButton_clicked() {
  // Создаем экземпляр второго окна
  tetris *gameWindow = new tetris();

  // Скрываем текущее окно
  this->hide();

  // Показываем новое окно
  gameWindow->show();
}

void mainwindow::on_pushButton_2_clicked() {
  // Создаем экземпляр второго окна
  snake *gameWindow = new snake();

  // Скрываем текущее окно
  this->hide();

  // Показываем новое окно
  gameWindow->show();
}
