
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
    :QLabel(parent),value(v),okToDrag(0),under(0),over(0),pile(0),moving(0)
{
    suit = suits(v / 13);
    pip = pips(v % 13);
    color = (DIAMONDS==suit || HEARTS== suit ) ?RED:BLACK;
    Faceup(false);
}

Card::Card(pips p, suits s, QWidget *parent)
    :QLabel(parent), pip(p),suit(s),okToDrag(0),under(0),over(0),pile(0),moving(0)
{
    color = (DIAMONDS==s || HEARTS== s ) ?RED:BLACK;
    value = 13 * s + p;
    Faceup(false);
}

// Couting from buttom to top
int Card::StackSize()
{
    int size = 0;
    for(Card *c = this; c!=NULL; ++size, c = c->over);
    return size;
}

// reverse card and adjust Image
void Card::Faceup(bool f)
{
    faceup = f;
    setPixmap(QPixmap::fromImage(faces[f?value:52]));
}

void Card::mousePressEvent(QMouseEvent *ev){
    switch(ev->button()){
    case Qt::LeftButton:
        startDragPos=pos();
        mouseDownOffset=pos()-ev->globalPos();
        okToDrag=faceup && pile->CanBeDragged(this);
        break;
    case Qt::RightButton:
        popUpPos=pos();
        popUpCard=this;
        move(pos()+QPoint(0,-20));
        break;
    default: ;
    }
}

void Card::mouseMoveEvent(QMouseEvent *ev){

    QPoint point =ev->globalPos()+mouseDownOffset;
    QPoint moved =point-pos();

    if(moving)
        AdjustPositions(point,pile?pile->Delta():QPoint(0,10));
    else
        if(okToDrag && moved.manhattanLength()>4)
            // the mouse has moved more than 4 pixel since the oldposition
            moving=true;
}

void Card::mouseReleaseEvent(QMouseEvent *ev){
    if(ev->buttons()) return;
    if(popUpCard){
        popUpCard->move(popUpPos);//restore card position
        popUpCard=NULL;
        return;
    }
    if(moving && pile)
        pile ->FindClosestDrop(this);
    else
        if(pile){
            QPoint point =ev->globalPos()+mouseDownOffset;
            QPoint moved =point-pos();
            if(moved.manhattanLength()<=4)
                pile->onClickEvent(this);
        }
    moving=false;
    okToDrag=false;
}

void Card::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if(pile) pile->mouseDoubleClickEvent(this);
    if(!over) // try to play off card
        Playoff();
}

void Card::Playoff()
{
    pile->onClickEvent(this);
}

void Card::Move(Pile *to, bool expose)
{
    to->AcceptCards(this, expose, false);
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

// pile is in WASTE, align with current pile
void Card::AlignWithPile()
{

    if(pile){
        QPoint cardPos = pile->pos();
        move(cardPos);
    }
}

void Card::Animate(QPoint newPos)
{

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
