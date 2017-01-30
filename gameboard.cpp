#include "card.h"
#include "klondike.h"
#include "gameboard.h"
#include "ui_gameboard.h"

Game *game;

GameBoard::GameBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameBoard)
{
    ui->setupUi(this);

    Card::Initialize();

    game = NULL;
}

GameBoard::~GameBoard()
{
    delete ui;
}

void GameBoard::on_actionKlondike_triggered()
{
    game = new Klondike(ui->centralWidget);
    game->ReDeal(EASY);
}
