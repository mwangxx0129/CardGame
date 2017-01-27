#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QList>
enum hardtype{REPEAT,EASY,MEDIUM,HARD};
class Pile;
class Card;

class Game
{

protected:
    QWidget *parent;
    QList<Pile *> piles;
public:
    Game(QWidget *par);
    void AddPile(Pile *p);
    virtual ~Game();
    void Clear();
    virtual void ReDeal(hardtype h = REPEAT)=0;
    virtual bool PlayOff(Card *c);
    virtual void PlayOffAll();
    virtual void OnFieldDoubleClick(Card *){}
    virtual void OnFiledClick(Card *c){}
    virtual void OnDealClick(Card *c){}
    virtual void OnDealtClick(Card *c){}
    virtual void OnFreeCellClick(Card *c){}
    virtual void CheckWin();
    virtual QString GameName()=0;
    virtual int FreeMoves(){return 0;} // calculate max move fo freecell
    friend class Pile;

};

#endif // GAME_H
