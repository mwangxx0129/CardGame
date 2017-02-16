#ifndef RULE_H
#define RULE_H

class Pile;
class Card;
class Rule  //abstract base class
{
public:
    virtual bool Enforce(Pile *p, Card *c)=0;
};

class RuleBaseNone:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleBaseKing:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleBaseAce:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleNoStack:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleStackSameSuit:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleStackAlternateColor:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleStackMinusOne:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleStackPlusOne:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleStackAny:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleStackOneAtATime:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleStack13:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleStackLengthLimited:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleMoveSameSuit:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleMoveAltColor:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleMoveSeqDecreasing:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleMoveSeqIncreasing:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleMoveLengthLimited:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleMoveNone:public Rule{
    bool Enforce(Pile *p, Card *c);
};

class RuleMoveOneAtATime:public Rule{
    bool Enforce(Pile *p, Card *c);
};

#endif // RULE_H
