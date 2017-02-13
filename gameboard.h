#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>

class Card;
class Game;
namespace Ui {
class GameBoard;
}

class GameBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = 0);
    ~GameBoard();

private slots:
    void on_actionKlondike_triggered();

    void on_actionFreeCell_triggered();

    void on_actionSpider_triggered();

    void on_actionRedeal_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionPlay_off_triggered();

    void on_actionUndo_triggered();

private:
    Ui::GameBoard *ui;
    Card *deck[53];
    void on_actionGame_triggered(QString);

};

#endif // GAMEBOARD_H
