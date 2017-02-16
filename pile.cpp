#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
#include "pile.h"
#include "card.h"
#include "game.h"
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
    Card *c = bottom;
    while(c)
    {
        bottom = c->over;
        delete c;
        c = bottom;
    }
    // TODO DragRule and DropRule
}

// Accept Cards
void Pile::AcceptCards(Card *c, bool expose, bool record)
{
    QPoint cardPosition;
    if(c == NULL) return;
    if (record) new CardMove(c, c->pile, this);
    if (c->pile) // is the card in a pile now?
        c->pile->ReleaseCards(c, expose);
    if (top) // pile not empty
    {
        cardPosition = top->pos()+Delta();
        c->under = top;
        top->over = c;
    }else{
        cardPosition = pos();
        bottom = c;
    }

    c->Faceup(expose);
    c->pile = this;
    top = c->AdjustPositions(cardPosition, Delta());
    if(Type() == FOUNDATION && top->Pip() == KING) game->CheckWin();
}

// Called by original pile
// Cut off the link between original pile and card
void Pile::ReleaseCards(Card *c, bool expose)
{
    if(c && c->pile && c->under){
        top = c->under;
        top->over = NULL;
        c->under = NULL;
        if(this->Type() != STOCK)
            top->Faceup(expose);
    }else{
        top = NULL;
        bottom = NULL;
    }

}

bool Pile::CanBeDragged(Card *c)
{
    int i =0;
    bool ok =true;
    while(ok&&DragRule(i)){
        ok = DragRule(i++)->Enforce(this, c);
    }
    return ok;
}

bool Pile::CanBeDropped(Card *c)
{
    int i =0;
    bool ok =true;
    while(ok&&DropRule(i)){
        ok = DropRule(i++)->Enforce(this, c);
    }
    return ok;
}

// find the closest pile,which will accept Card
void Pile::FindClosestDrop(Card *c)
{
    const int NUM = 3;
    QPoint drop = c->pos();
    Pile *closest[NUM] = {NULL, NULL, NULL};
    int distance[NUM] = {10000, 20000, 30000};
    for (int i = 0; i<game->piles.count(); i++)
    {
        Pile *p = game->piles[i];
        if (p == c->pile)
            continue;
        QPoint diff = drop - (p->top?p->top->pos():p->pos());
        int dist = diff.manhattanLength();
        for (int j = 0; j < NUM; j++)
        {
            if (dist < distance[j])
            {
                std::swap(dist, distance[j]);
                std::swap(p, closest[j]);
            }
        }
    }
    for (int i = 0; i < NUM; i++)
    {
        if (closest[i] && closest[i]->CanBeDropped(c))
        {
            closest[i]->AcceptCards(c);
            return;
        }
    }
    QPoint p = c->under?(c->under->pos()+c->pile->Delta()/(c->under->faceup?1:2)):c->pile->pos();
    c->AdjustPositions(p, c->pile->delta); // put them back if no move
}

void Pile::AddDropRules(int n ...)
{
    va_list lp;
    va_start(lp,n);
    int i = 0;
    while(i<n)
        DropRule(i++,va_arg(lp,Rule*));
    DropRule(i,NULL);
    va_end(lp);
}

void Pile::AddDragRules(int n ...)
{
    va_list lp;
    va_start(lp,n);
    int i = 0;
    while(i<n)
        DragRule(i++,va_arg(lp,Rule*));
    DragRule(i,NULL);
    va_end(lp);
}

void Pile::mouseReleaseEvent(QMouseEvent *)
{
    //game->OnDealEmptyClick(NULL);
}

void Pile::mousePressEvent(QMouseEvent *)
{
    game->OnDealEmptyClick(NULL);
}

//Methods for inheriting classes----------------------------------------
PileTableau::PileTableau(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent){

}

pileType PileTableau::Type()
{
    return TABLEAU;
}

void PileTableau::onClickEvent(Card *c)
{
    game->OnTableauClick(c);
}

void PileTableau::mouseDoubleClickEvent(Card *c)
{

    game->OnFieldDoubleClick(c);
}


PileStock::PileStock(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent)
{
}

pileType PileStock::Type()
{
    return STOCK;
}

void PileStock::onClickEvent(Card *c)
{
    game->OnDealClick(c);
}

PileWaste::PileWaste(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent)
{

}

pileType PileWaste::Type()
{
    return WASTE;
}

PileFoundation::PileFoundation(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent)
{

}

pileType PileFoundation::Type()
{
    return FOUNDATION;
}

PileFreeCell::PileFreeCell(int x, int y, int dx, int dy, QWidget *parent):
    Pile(x,y,dx,dy,parent)
{

}

pileType PileFreeCell::Type()
{
    return FREE_CELL;
}
