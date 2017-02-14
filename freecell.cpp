#include "card.h"
#include "pile.h"
#include "freecell.h"

FreeCell::FreeCell(QWidget *par):
    Game(par)
{}

void FreeCell::ReDeal(hardtype h)
{
    Clear();

    // create and shuffle
    Card* Deck[52];
    for (int i = 0; i < 52; i++)
        Deck[i] = new Card(i, parent); // create face down
    Shuffle(Deck, 52);
    // now create board layout

    for (int i = 0; i < 4; i++)
        foundation[i] = new PileFoundation(430+82*i, 10, 0, 0, parent);
    foundation[0]->AddDropRules(4, new RuleStackSameSuit(),
                                new RuleStackPlusOne(),
                                new RuleBaseAce(),
                                new RuleMoveOneAtATime());
    foundation[0]->AddDragRules(0);

    for (int i = 0; i < 4; i++)
        freecell[i] = new PileFreeCell(20+82*i, 10, 0, 0, parent);
    freecell[0]->AddDropRules(2, new RuleMoveOneAtATime(),
                              new RuleStackOneAtATime());
    freecell[0]->AddDragRules(0);

    for (int i = 0; i < 8; i++)
        tableau[i] = new PileTableau(61+82*i, 120, 0, 18, parent);
    tableau[0]->AddDropRules(2, new RuleStackAlternateColor,
                             new RuleStackMinusOne());
    tableau[0]->AddDragRules(2, new RuleMoveAltColor(),
                             new RuleMoveSeqDecreasing());

    int i = 0;
    // now deal with cards
    for(int pass = 0; pass < 8 && i < 52; pass++)
        for(int pile = 0; pile < 8 && i <52; pile ++)
            Deck[i++]->Move(tableau[pile], true);
}

QString FreeCell::GameName()
{
    return "FreeCell";
}
