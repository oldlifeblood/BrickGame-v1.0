#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tetrisgame(nullptr),
    snakegame(nullptr)
{
    ui->setupUi(this);
    setFixedSize(700, 500);
    connect(ui->pushButtonTetris, &QPushButton::clicked, this, &MainWindow::on_pushButtonTetris_clicked);
    connect(ui->pushButtonSnake, &QPushButton::clicked, this, &MainWindow::on_pushButtonSnake_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (tetrisgame) delete tetrisgame;

}

void MainWindow::on_pushButtonTetris_clicked()
{
    if (!tetrisgame) {
        tetrisgame = new TetrisGame(this);
        connect(tetrisgame, &TetrisGame::firstWindow, this, &MainWindow::show);
        tetrisgame->setModal(true);
        tetrisgame->show();
        connect(tetrisgame, &TetrisGame::backButtonClicked, this, &MainWindow::backButtonClicked);
    } else {
        tetrisgame->show();
    }
}

void MainWindow::on_pushButtonSnake_clicked()
{
    if (!snakegame) {
        snakegame = new SnakeGame(this);
        connect(snakegame, &SnakeGame::secondWindow, this, &MainWindow::show);
        snakegame->setModal(true);
        snakegame->show();
        connect(snakegame, &SnakeGame::backButtonClicked, this, &MainWindow::backButtonClicked);
    } else {
        snakegame->show();
    }
}


void MainWindow::backButtonClicked()
{
    if(tetrisgame) {
        tetrisgame->hide();
        delete tetrisgame;
        tetrisgame = nullptr;
    } else if(snakegame) {
        snakegame->hide();
        delete snakegame;
        snakegame = nullptr;
    }
}
