#include "gameboard.h"
#include "ui_gameboard.h"

GameBoard::GameBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameBoard)
{
    ui->setupUi(this);
}

GameBoard::~GameBoard()
{
    delete ui;
}
