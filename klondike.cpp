#include "card.h"
#include "pile.h"
#include "klondike.h"

//----------------------------------------------------------------------|
Klondike::Klondike(QWidget *par)
    :Game(par)
{}

//----------------------------------------------------------------------|
void Klondike::ReDeal(hardtype h){
    Clear();
    diffculty = h;
    // create and shuffle
    Card* Deck[52];
    for (int i = 0; i < 52; i++)
        Deck[i] = new Card(i, parent);
    Shuffle(Deck, 52);

    // now create board layout
    for (int i = 0; i < 4; i++)
        foundation[i] = new PileFoundation(266+82*i, 10, 0, 0, parent);
    foundation[0]->AddDropRules(4, new RuleStackSameSuit(),
                                new RuleStackPlusOne(),
                                new RuleBaseAce(),
                                new RuleMoveOneAtATime());
    foundation[0]->AddDragRules(0);

    for (int i = 0; i < 7; i++)
        tableau[i] = new PileTableau(20+82*i, 120, 0, 18, parent);
    tableau[0]->AddDropRules(3, new RuleStackAlternateColor,
                             new RuleBaseKing(),
                             new RuleStackMinusOne());
    tableau[0]->AddDragRules(2, new RuleMoveAltColor(),
                             new RuleMoveSeqDecreasing());

    deal = new PileStock(20, 10, 0, 0, parent);
    deal->AddDropRules(2, new RuleBaseNone(),
                       new RuleNoStack());
    deal->AddDragRules(1, new RuleMoveNone());

    waste = new PileWaste(100, 10, 16, 1, parent);
    waste->AddDropRules(2, new RuleBaseNone(),
                        new RuleNoStack());
    waste->AddDragRules(1, new RuleMoveOneAtATime());

    // now deal with cards
    int i =0;

    for (int pass = 0; pass < 7; pass++)
        for (int pile = pass; pile < 7; pile++)
            Deck[i++]->Move(tableau[pile], pass == pile);
    while (i < 52)
        Deck[i++]->Move(deal,false);
}

//----------------------------------------------------------------------|
QString Klondike::GameName(){
    return "Klondike";
}

//----------------------------------------------------------------------|
void Klondike::DealAction(Card * c){
    // deal card to Waste
    for(int i = 0; i<3 && deal; i++)
    {
        waste->AcceptCards(deal->Top(), true, false);
        if(i==0) c->AlignWithPile();
    }
}
//----------------------------------------------------------------------|
void Klondike::OnTableauClick(Card *c){
    if(c) PlayOff(c);
}
//----------------------------------------------------------------------|
void Klondike::OnDealClick(Card *c){
    DealAction(c);
}
//----------------------------------------------------------------------|
void Klondike::OnWasteClick(Card *c){
    if(c) PlayOff(c);
}

void Klondike::OnDealEmptyClick(Card *)
{
    // push back to Stock
    if(deal->Empty()){
        while(!waste->Empty()){
            deal->AcceptCards(waste->Top());
            deal->Top()->Faceup(false);
        }
    }
}
