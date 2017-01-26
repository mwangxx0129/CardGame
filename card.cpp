#include "pile.h"
#include "card.h"

QImage Card::faces[53];
bool Card::initialized = false;

void Card::Initialize()
{
    if(initialized) return;
    initialized = true;
    char suit[] = {'c','d','h','s'};
    char pip[] = {'1','2','3','4','5','6','7','8','9','a','b','c','d'};
    QString fname =":/cards/cl.bmp";
    int n = 0;
    for(int s = CLUBS; s <= SPADES; ++s)
    {
        // TODO
    }
    faces[n] =QImage(":/card/zCardBack.bmp");
}

