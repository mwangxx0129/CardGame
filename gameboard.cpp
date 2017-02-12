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
    resize(1000,700);
    Card::Initialize();
    game = NULL;
}

GameBoard::~GameBoard()
{
    delete ui;
}

void GameBoard::on_actionKlondike_triggered()
{
    on_actionGame_triggered("Klondike");
}

void GameBoard::on_actionFreeCell_triggered()
{
    on_actionGame_triggered("FreeCell");
}

void GameBoard::on_actionSpider_triggered()
{
    on_actionGame_triggered("Spider");
}

void GameBoard::on_actionGame_triggered(QString name)
{
    //qsrand(t.elapsed());
    setWindowTitle(name);
    //setSizePolicy(QSizePolicy());
    if(game) game->Clear();
    switch (name.at(0).toLatin1()) {
    case 'K':
        game = new Klondike(ui->centralWidget);
        break;
    case 'F':
        game = new FreeCell(ui->centralWidget);
        break;
    case 'S':
        game = new Spider(ui->centralWidget);
        break;
    default:
        break;
    }
    ui->menuGame->setTitle(game->GameName());
    game->ReDeal(MEDIUM);
}

void GameBoard::on_actionRedeal_triggered()
{
    on_actionGame_triggered(NULL != game ? game->GameName():"Klondike");
}
