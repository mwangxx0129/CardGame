#include "pile.h"
#include "card.h"
#include "gameboard.h"
#include "cardmove.h"


extern GameBoard *MainApp;
extern Game *game;
extern QList<Pile *> piles;

// static member data allocation

Rule *PileStock::dragRules[DRAGLAST];
Rule *PileStock::dropRules[DROPLAST];

Rule *PileFoundation::dragRules[DRAGLAST];
Rule *PileFoundation::dropRules[DROPLAST];

Rule *PileTableau::dragRules[DRAGLAST];
Rule *PileTableau::dropRules[DROPLAST];

Rule *PileFreeCell::dragRules[DRAGLAST];
Rule *PileFreeCell::dropRules[DROPLAST];

Rule *PileWaste::dragRules[DRAGLAST];
Rule *PileWaste::dropRules[DROPLAST];

// constructor
Pile::Pile(int x, int y,   //position of upper left corner
           int dx, int dy, //offset to next card
           // stock(0,0) foundation(0,0) table(0, dy) wast (dx,tiny dy)
           // if not face up, half dy on tableau
           QWidget *parent):
    QLabel(parent),delta(QPoint(dx,dy)),top(0),bottom(0)
{
    topLeft.setX(x);
    topLeft.setY(y);
    num = 0;

    game->AddPile(this);
    move(x, y);
    resize(71,96);
    setFrameShape(Box);
    setLineWidth(2);
    show();
}
Pile::~Pile()
{
    //TODO
}

void Pile::AddOneCard()
{
    ++num;
}
//void mouseReleaseEvent(QMouseEvent *){

//}
//Methods for inheriting classes----------------------------------------
PileTableau::PileTableau(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent){

}


PileStock::PileStock(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent)
{
}

PileWaste::PileWaste(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent)
{

}

PileFoundation::PileFoundation(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent)
{

}
