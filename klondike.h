#ifndef KLONDIKE_H
#define KLONDIKE_H
#include "game.h"
#include <QWidget>
class Pile;

class Klondike: public Game
{
    Pile *deal;
    Pile *waste;
    Pile *foundation[4];
    Pile *tableau[7];
    hardtype diffculty;
public:
    Klondike(QWidget *par);
    void ReDeal(hardtype h = EASY);
    QString GameName();


    void DealAction(Card *c);
    void OnTableauClick(Card *c);
    void OnDealClick(Card *c);
    void OnWasteClick(Card *c);
    void OnDealEmptyClick(Card *);
};
#endif // KLONDIKE_H
