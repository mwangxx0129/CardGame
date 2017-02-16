#ifndef FREECELL_H
#define FREECELL_H
#include "game.h"
#include <QWidget>
class Pile;


class FreeCell: public Game
{
private:
    Pile *freecell[4];
    Pile *foundation[4];
    Pile *tableau[8];
public:
    FreeCell(QWidget *par = 0);
    void ReDeal(hardtype h = REPEAT);
    QString GameName();
    int FreeMoves(){return 1;}
};

#endif // FREECELL_H
