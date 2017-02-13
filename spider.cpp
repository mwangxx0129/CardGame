#include "card.h"
#include "pile.h"
#include "spider.h"

Spider::Spider(QWidget *par):
    Game(par)
{}

void Spider::ReDeal(hardtype h)
{
    Clear();

    // create and shuffle
    Card* Deck[104];
    for (int i = 0; i < 104; i++)
        Deck[i] = new Card(i%13, parent);
    Shuffle(Deck, 104);

    // now create board layout
    for(int i = 0; i< 10; i++)
        tableau[i] = new PileTableau(20+82*i, 10, 0, 18, parent);
    tableau[0]->AddDropRules(3, new RuleStackSameSuit,
                             new RuleBaseKing(),
                             new RuleStackMinusOne());
    tableau[0]->AddDragRules(2, new RuleMoveSameSuit(),
                             new RuleMoveSeqDecreasing());

    for (int i = 0; i < 8; i++)
        foundation[i] = new PileFoundation(20+20*i, 500, 0, 0, parent);
    foundation[0]->AddDropRules(4, new RuleStackSameSuit(),
                                new RuleStackPlusOne(),
                                new RuleBaseAce(),
                                new RuleStack13());
    foundation[0]->AddDragRules(0);

    for (int i = 0; i < 5; i++)
        stock[i] = new PileStock(676+8*i, 500, 0, 0, parent);
    stock[0]->AddDropRules(1, new RuleBaseNone());
    stock[0]->AddDragRules(1, new RuleMoveNone());

    int i = 0;
    // now deal with cards
    for(int pass = 0; pass < 6 && i < 44; pass++)
        for(int pile = 0; pile < 10 && i <44; pile++)
            Deck[i++]->Move(tableau[pile], false);

    for(int pile = 4; pile < 10; pile++)
        Deck[i++]->Move(tableau[pile], true);

    for(int pile = 0; pile < 4; pile++)
        Deck[i++]->Move(tableau[pile], true);


    for(int pile = 0; pile < 5; pile ++)
        for (int stack = 0; stack < 10; stack ++)
            Deck[i++]->Move(stock[pile], false);
}

QString Spider::GameName()
{
    return "Spider";
}

void Spider::OnDealClick(Card *c)
{
    Pile *p = c->Pilep();
    for (int stack = 0; stack < 10; stack ++)
    {
        tableau[stack]->AcceptCards(p->Top(), true, true);
    }
}

void Spider::OnFieldDoubleClick(Card *c)
{
    Pile *p = c->Pilep();

    // find empty foundation
    int i = 0;
    while(i<8 &&foundation[i] && foundation[i]->Top()) i++;


    // check CanBeDropped
    if(!foundation[i]->CanBeDropped(p->Top()))
        return;

    // store them in foundation[i]
    int k = 0;
    while(k++ < 13)
        foundation[i]->AcceptCards(p->Top());
}
