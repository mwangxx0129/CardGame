#include "klondike.h"

Klondike::Klondike(QWidget *par)
    :Game(par)
{}
void Klondike::ReDeal(hardtype h){}
QString Klondike::GameName(){
    return "Klondike";
}
void Klondike::DealAction(){}
void Klondike::OnTableauClick(Card *c){}
void Klondike::OnDealClick(Card *c){}
void Klondike::OnWasteClick(Card *c){}
