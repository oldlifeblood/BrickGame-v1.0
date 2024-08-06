#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tetrisgamewindow.h"
#include "snakegamewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace s21;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void backButtonClicked();

private slots:
    void on_pushButtonTetris_clicked();
    void on_pushButtonSnake_clicked();


private:
    Ui::MainWindow *ui;
    TetrisGame *tetrisgame;
    SnakeGame *snakegame;
};

#endif // MAINWINDOW_H
