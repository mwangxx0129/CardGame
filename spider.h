#ifndef SPIDER_H
#define SPIDER_H
#include "game.h"
#include <QWidget>
class Pile;

class Spider: public Game
{
private:
    Pile *stock[4];
    Pile *foundation[4];
    Pile *tableau[10];
public:
    Spider(QWidget *par);
    void ReDeal(hardtype h = REPEAT);
    QString GameName();
};

#endif // SPIDER_H
