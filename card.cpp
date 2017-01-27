#include "pile.h"
#include "card.h"

QImage Card::faces[53];
bool Card::initialized = false;


Card::Card(int v, QWidget *parent)
{
    this->setPalette(parent);
    value = v;
}

Card::Card(pips p, suits s, QWidget *parent)
{
    pip = p;
    suit = s;
    if(s == DIAMONDS || s == HEARTS ){
        cardColor = RED;
    }else{
        cardColor = BLACK;
    }
    setParent(parent);
    //value = v;
    this->id = id;
    on = NULL;
    faceup = true;
    popUpCard = NULL;
}

void Card::Initialize()
{
    if(initialized) return;
    initialized = true;
    char suit[] = {'c','d','h','s'};
    char pip[] = {'1','2','3','4','5','6','7','8','9','a','b','c','d'};
    QString fname =":/cards/c1.bmp";
    int n = 0;

    // init card 0-52
    for(int s = CLUBS; s <= SPADES; ++s)
    {
        fname[8] = suit[s];
        for(int p = ACE; p <= KING; p++)
        {
            fname[9] = pip[p];
            face[n++] = QImage(fname);
        }
    }
    // init card 53
    faces[n] =QImage(":/cards/zCardBack.bmp");
}

Card::~Card(){

}

