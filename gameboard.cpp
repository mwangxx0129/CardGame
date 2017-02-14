#include <QTime>
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
    if(game) game->Clear();
    // seed based on current time
    qsrand(QTime::currentTime().msec());
    game = new Klondike(ui->centralWidget);
    setWindowTitle(game->GameName());
    game->ReDeal(MEDIUM);
}

void GameBoard::on_actionFreeCell_triggered()
{
    if(game) game->Clear();
    // seed based on current time
    qsrand(QTime::currentTime().msec());
    game = new FreeCell(ui->centralWidget);
    setWindowTitle(game->GameName());
    game->ReDeal(MEDIUM);
}

void GameBoard::on_actionSpider_triggered()
{
    if(game) game->Clear();
    // seed based on current time
    qsrand(QTime::currentTime().msec());
    game = new Spider(ui->centralWidget);
    setWindowTitle(game->GameName());
    game->ReDeal(MEDIUM);
}

void GameBoard::on_actionRedeal_triggered()
{
    if(game) {
        game->Clear();
        game->ReDeal(MEDIUM);
    }
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
