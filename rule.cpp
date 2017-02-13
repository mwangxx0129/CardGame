#include "rule.h"
#include "pile.h"
#include "card.h"
#include "gameboard.h"

extern GameBoard *MainApp;
extern Game *game;

bool RuleBaseNone::Enfore(Pile *p, Card *c)
{
    return false;
}

bool RuleBaseKing::Enfore(Pile *p, Card *c)
{
    return !p->Empty() || c->Pip()==KING;
}

bool RuleBaseAce::Enfore(Pile *p, Card *c)
{
    return !p->Empty() || c->Pip()==ACE;
}

bool RuleNoStack::Enfore(Pile *p, Card *c)
{
    int cs = c->StackSize();
    int fm = game->FreeMoves();
    fm>>= p->Empty()?1:0;
    return cs <=fm;
}

bool RuleStackSameSuit::Enfore(Pile *p, Card *c)
{
    return p->Empty() || c->Suit() == p->Top()->Suit();
}

bool RuleStackAlternateColor::Enfore(Pile *p, Card *c)
{
    return p->Empty() || c->Color() != p->Top()->Color();
}

bool RuleStackMinusOne::Enfore(Pile *p, Card *c)
{
    return p->Empty() || c->Pip() - p->Top()->Pip() == -1;
}

bool RuleStackPlusOne::Enfore(Pile *p, Card *c)
{
    return p->Empty() || c->Pip() - p->Top()->Pip() == 1;
}

bool RuleStackAny::Enfore(Pile *p, Card *c)
{
    return true;
}

bool RuleStackOneAtATime::Enfore(Pile *p, Card *c)
{
    return c->Over()==NULL;
}

bool RuleStack13::Enfore(Pile *p, Card *c)
{
    Card* temp = c;
    bool ok = true;
    int val = c->Pip();
    suits s = c->Suit();
    while ( ok &&
            (ok =(temp->Pip() == val &&
                  temp->Suit() == s) )
            && val < KING )
    {    val = (val + 1);
        temp = temp->Under();
        ok = temp;
    }
    return ok;
}

bool RuleStackLengthLimited::Enfore(Pile *p, Card *c)
{
    int cs = c->StackSize();
    int fm = game->FreeMoves();
    fm >>= p->Empty()?1:0;
    return cs <= fm;
}

bool RuleMoveSameSuit::Enfore(Pile *p, Card *c)
{
    bool ok = true;
    while (ok && c->Over())
    {
        ok = c->Suit() == c->Over()->Suit();
        c = c->Over();
    }
    return ok;
}

bool RuleMoveAltColor::Enfore(Pile *p, Card *c)
{
    bool ok = true;
    while (ok && c->Over())
    {
        ok = c->Color() != c->Over()->Color();
        c = c->Over();
    }
    return ok;
}

bool RuleMoveSeqDecreasing::Enfore(Pile *p, Card *c)
{
    bool ok = true;
    while (ok && c->Over() )
    {
        ok = 1 == c->Pip() - c->Over()->Pip();
        c = c->Over();
    }
    return ok;
}

bool RuleMoveSeqIncreasing::Enfore(Pile *p, Card *c)
{
    bool ok = true;
    while (ok && c->Over())
    {
        ok = 1 == c->Over()->Pip() - c->Pip();
        c = c->Over();
    }
    return ok;
}

bool RuleMoveLengthLimited::Enfore(Pile *p, Card *c)
{
    return c->StackSize() <= game->FreeMoves();
}

bool RuleMoveNone::Enfore(Pile *p, Card *c)
{
    return false;
}

bool RuleMoveOneAtATime::Enfore(Pile *p, Card *c)
{
    return !c->Over();
}
