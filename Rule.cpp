#include "Rule.hpp"

Rule::Rule(string original, string replacement)
{
    this->original = new ExpressionTree(original);
    this->replacement = new ExpressionTree(replacement);
}

void Rule::applyRule(ExpressionTree *expression)
{
    //ExpressionTree *result;

    match(original->peek(), expression->peek());

    //return result;
}

void Rule::match(Node *P, Node *T)
{
    if (compare(P, T))
    {
        cout << "Found a pattern!\n";
        //TODO: replace the original tree with replacement tree
        return;
    }
    //TODO: apply to the degree of the tree node, not just left and right
    if (T)
        match(P, T->l);
    if (T)
        match(P, T->r);
}

bool Rule::compare(Node *P, Node *U)
{
    //printf("%s %s\n", U->d, P->d);

    if (!U && !P)
    {
        return true;
    }
    else if (!U)
    {
        return false;
    }
    else if (!P)
    {
        return false;
    }

    //TODO: add step 1: "don't care" logic
    //if(P->d == dontcare) return true;

    //step 2: compare the operator
    if (!(P->d == U->d))
    {
        return false;
    }

    //step 3: compare the chlidren nodes recursively
    //TODO: apply to the degree of the tree node, not just left and right
    if (!compare(P->l, U->l))
    {
        return false;
    }
    if (!compare(P->r, U->r))
    {
        return false;
    }

    return true;
}
