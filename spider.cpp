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

    for (int i = 0; i < 8; i++)
        foundation[i] = new PileFoundation(20+82*i, 500, 0, 0, parent);

    for (int i = 0; i < 5; i++)
        stock[i] = new PileStock(676+8*i, 500, 0, 0, parent);

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
