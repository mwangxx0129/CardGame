#ifndef CARDMOVE_H
#define CARDMOVE_H
#include <QStack>

class Pile;
class Card;

class CardMove
{
    Card *card;
    Pile *from;
    Pile *to;
    int count:16;
    bool wasFaceUp:1;
    static QStack<CardMove*> undostack;
public:
    CardMove(Card *c, Pile *fr, Pile *t);
    CardMove(int n);
    static void UndoMove();
    static void Clear();
};

#endif // CARDMOVE_H
