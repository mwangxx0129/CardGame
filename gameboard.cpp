#include "card.h"
#include "klondike.h"
#include "freecell.h"
#include "spider.h"
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
    if(game) game->Clear();
    game = new Klondike(ui->centralWidget);
    game->ReDeal(MEDIUM);
}

void GameBoard::on_actionFreeCell_triggered()
{
    if(game) game->Clear();
    game = new FreeCell(ui->centralWidget);
    game->ReDeal(MEDIUM);
}

void GameBoard::on_actionSpider_triggered()
{
    if(game) game->Clear();
    game = new Spider(ui->centralWidget);
    game->ReDeal(MEDIUM);
}
