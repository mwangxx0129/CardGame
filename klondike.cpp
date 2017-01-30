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
    // create and shuffle
    Card* Deck[52];
    for (int i = 0; i < 52; i++)
        Deck[i] = new Card(i, parent); // create face down
    Shuffle(Deck, 52);

    // now create board layout
    deal = new PileStock(20, 10, 0, 0, parent);

    waste = new PileWaste(100, 10, 16, 1, parent);

    for (int i = 0; i < 4; i++)
        foundation[i] = new PileFoundation(266+82*i, 10, 0, 0, parent);

    for (int i = 0; i < 7; i++)
        tableau[i] = new PileTableau(20+82*i, 120, 0, 18, parent);

    // now deal with cards
    int i =0;

    for (int pass = 0; pass < 7; pass++)
        for (int pile = pass; pile < 7; pile++)
        {
            if (pass == pile)
                Deck[i]->Faceup(true);
            Deck[i++]->Move(tableau[pile]);
        }

    while (i < 52)
        Deck[i++]->Move(deal);
}

//----------------------------------------------------------------------|
QString Klondike::GameName(){
    return "Klondike";
}
//----------------------------------------------------------------------|
void Klondike::DealAction(){}
//----------------------------------------------------------------------|
void Klondike::OnTableauClick(Card *c){}
//----------------------------------------------------------------------|
void Klondike::OnDealClick(Card *c){}
//----------------------------------------------------------------------|
void Klondike::OnWasteClick(Card *c){}
