
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
    color = (DIAMONDS==s || HEARTS== s ) ?RED:BLACK;
    Faceup(false);
    under = NULL;
    over = NULL;
}

Card::Card(pips p, suits s, QWidget *parent)
    :QLabel(parent), pip(p),suit(s)
{
    color = (DIAMONDS==s || HEARTS== s ) ?RED:BLACK;
    value = 13 * s + p;
    Faceup(false);
    under = NULL;
    over = NULL;
}

// Couting from buttom to top
int Card::StackSize()
{
    int size = 0;
    for(Card *c = this; c!=NULL; ++size, c = c->over);
    return size;
}

void Card::Faceup(bool f)
{
    setPixmap(QPixmap::fromImage(faces[f?value:52]));
}

void Card::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() ==Qt::LeftButton){
        startDragPos = pos();
        mouseDownOffset = pos()- ev->globalPos();
        okToDrag = faceup && pile->CanBeDragged(this);
    }else if(ev->button() == Qt::RightButton)
    {
        popUpPos=pos();
        popUpCard=this;
        move(pos()+QPoint(0,-20));
    }
}

void Card::mouseMoveEvent(QMouseEvent *ev)
{
    Card * c = this;

    QPoint point =ev->globalPos()+mouseDownOffset;
    QPoint moved =point-pos();
    if(okToDrag && moved.manhattanLength()>4)
        // the mouse has moved more than 4 pixel since the oldposition
        moving=true;
    else
        AdjustPositions(point,pile?pile->Delta():QPoint(0,10));
}

void Card::mouseReleaseEvent(QMouseEvent *ev)
{

}

void Card::Move(Pile *to, bool expose)
{
    Faceup(expose);

    QPoint topLeft = to->pos();
    QPoint delta = to ->Delta();
    int num = to->Bottom()->StackSize();

    to->AcceptCards(this, expose, true);

    int x = topLeft.x() + delta.x() * num;
    int y = topLeft.y() + delta.y() * num;

    move(x,y);
    raise();
    show();
}

Card *Card::AdjustPositions(QPoint newPos, QPoint delta)
{
    Card *c =this;
    Card *top;
    do{
        c->move(newPos);
        c->raise();
        c->show();
        newPos += (delta/(c-faceup?1:2));
        top =c;
        c->pile=pile;
        c=c->over;
    }while(c);
    return top;
}

void Card::Initialize()
{
    if(initialized) return;
    initialized = true;
    char suit[] = {'c','d','h','s'};
    char pip[] =
    {'1','2','3','4','5','6','7','8','9','a','b','c','d'};
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
