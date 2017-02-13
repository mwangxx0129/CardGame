#include "cardmove.h"
#include "card.h"
#include "pile.h"

QStack<CardMove*> CardMove::undostack;
CardMove::CardMove(Card *c, Pile *fr, Pile *t)
    :card(c),from(fr),to(t),count(0)
{
    wasFaceUp = c->Under()? c->Under()->Faceup():false;
    undostack.push(this);
}

CardMove::CardMove(int n)
    :count(n)
{
    undostack.push(this);
}

void CardMove::UndoMove()
{
    if(undostack.empty()) return;
    CardMove *u = undostack.pop();
    int n = u->count;
    do{
        if(n)
        {
            delete u;
            u = undostack.pop();
        }
        if(u->from->Top() && u->from->Top()->Faceup()!= u->wasFaceUp)
            u->from->Top()->Flip();
        u->from->AcceptCards(u->card, true, false);
        if(u->from->Type() == STOCK) u->card->Faceup(false);
        if(u->from->Type() == WASTE && n%3 == 0) u->card->AlignWithPile();
    }while(--n>0);
    delete u;
}

void CardMove::Clear()
{
    while(!undostack.empty()){
        delete undostack.pop();
    }
}



