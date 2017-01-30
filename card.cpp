
#include "card.h"
#include "pile.h"

QImage Card::faces[53];
bool Card::initialized = false;
QPoint Card::mouseDownOffset; // Distance to add to mouse pos to move
QPoint Card::startDragPos;
Qt::MouseButtons Card::buttonDown;
QPoint Card::popUpPos;
Card * Card::popUpCard;

Card::Card(int v, QWidget *parent)
    :QLabel(parent),value(v)
{
    int s = v % 13;
    if(s == DIAMONDS || s == HEARTS ){
        color = RED;
    }else{
        color = BLACK;
    }

    QPixmap image;
    faceup = false;
    if(faceup){
        image = QPixmap::fromImage(faces[value]);
    }else{
        image = QPixmap::fromImage(faces[52]);
    }

    setPixmap(image);

    under = NULL;
    over = NULL;
}

Card::Card(pips p, suits s, QWidget *parent)
    :QLabel(parent), pip(p),suit(s)
{
    if(s == DIAMONDS || s == HEARTS ){
        color = RED;
    }else{
        color = BLACK;
    }
    value = 13 * s + p;

    faceup = false;
    QPixmap image =
            faceup == true?
                QPixmap::fromImage(faces[value])
              :QPixmap::fromImage(faces[52]);

    setPixmap(image);


    under = NULL;
    over = NULL;
}

int Card::StackSize()
{
    int size = 1;

    // from current to down
    Card *c = this;
    while (c->under)
    {
        ++size;
        c = c->under;
    }

    // from current to up
    c = this;
    while(c->over)
    {
        ++size;
        c = c->over;
    }

    return size;
}

void Card::Faceup(bool f)
{
    faceup = f;
    if(faceup){
        setPixmap(QPixmap::fromImage(faces[value]));
    }else{
        setPixmap(QPixmap::fromImage(faces[52]));
    }
}

void Card::Move(Pile *to, bool expose)
{

    QPoint topLeft = to->TopLeft();
    QPoint delta = to ->Delta();
    int num = to->Num();
    to->AddOneCard();

    int x = topLeft.x() + delta.x() * num;
    int y = topLeft.y() + delta.y() * num;

    move(x,y);
    raise();
    show();
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
            faces[n++] = QImage(fname);
        }
    }
    // init card 53th image
    faces[n] =QImage(":/cards/zCardBack.bmp");
}

void Card::Flip()
{
    Faceup(!Faceup()); //reverse card
}

void Shuffle(Card *Deck[], int n)
{
    Card *temp;
    int k;
    while(n>0)
    {
        k = (uint) qrand() % n--;
        temp = Deck[k];
        Deck[k] = Deck[n];
        Deck[n] = temp;
        temp->raise();
    }
}
