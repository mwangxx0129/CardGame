#ifndef RULE_H
#define RULE_H

class Pile;
class Card;
class Rule  //abstract base class
{
public:
    virtual bool Enfore(Pile *p, Card *c)=0;
};



#endif // RULE_H
