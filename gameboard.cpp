#include "card.h"
#include "klondike.h"
#include "freecell.h"
#include "spider.h"
#include "gameboard.h"
#include "ui_gameboard.h"
#include "winningdialog.h"
#include "helpdialog.h"
#include "aboutdialog.h"
#include "cardmove.h"

Game *game;
WinningDialog *WinBox;

GameBoard::GameBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameBoard)
{
    ui->setupUi(this);
    resize(1000,700);
    Card::Initialize();
    game = NULL;
    WinBox = new WinningDialog();
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

void GameBoard::on_actionHelp_triggered()
{
    HelpDialog *h =  new HelpDialog();
    h->show();
}

void GameBoard::on_actionAbout_triggered()
{
    AboutDialog * a = new AboutDialog();
    a->show();
}

void GameBoard::on_actionExit_triggered()
{
    exit(1);
}

void GameBoard::on_actionPlay_off_triggered()
{
    game->PlayOffAll();
}

void GameBoard::on_actionUndo_triggered()
{
    CardMove::UndoMove();
}
