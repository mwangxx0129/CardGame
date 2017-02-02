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

private:
    Ui::GameBoard *ui;
    Card *deck[53];

};

#endif // GAMEBOARD_H
