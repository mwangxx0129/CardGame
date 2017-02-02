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

Pile::Pile(int x, int y,
           int dx, int dy,
           QWidget *parent):
    QLabel(parent),delta(QPoint(dx,dy)),top(0),bottom(0)
{
    setStyleSheet("border:2px solid rgb(46, 158, 49);");
    game->AddPile(this);
    move(x, y);
    resize(71,96);
    setFrameShape(Box);
    setLineWidth(2);
    show();
}

Pile::~Pile()
{
    Card *c = top;
    while(c != NULL)
    {
        delete c;
        c = c->under;
    }
}

void Pile::AcceptCards(Card *c, bool expose, bool record)
{
    if(bottom == NULL)
    {
        top = c;
        bottom = c;
    }else{
        Card * tmp = top;
        top = c;
        tmp->over = top;
        top->under = tmp;
    }
}

bool Pile::CanBeDragged(Card *c)
{

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

PileFreeCell::PileFreeCell(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent)
{

}
