#ifndef SPIDER_H
#define SPIDER_H
#include "game.h"
#include <QWidget>
class Pile;

class Spider: public Game
{
private:
    hardtype diffculty;
    Pile *stock[5]; // [5]
    Pile *foundation[8];// [8]
    Pile *tableau[10];
public:
    Spider(QWidget *par);
    void ReDeal(hardtype h = REPEAT);
    QString GameName();
};

#endif // SPIDER_H
