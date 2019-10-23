#ifndef REWRITE_RULE_h
#define REWRITE_RULE_h

#include "ExpressionTree.hpp"

class Rule
{
private:
    ExpressionTree *original, *replacement;
    void match(Node *P, Node *T);
    bool compare(Node *P, Node *U);

public:
    Rule(string original, string replacement);
    void applyRule(ExpressionTree *expression);
};

#endif // REWRITE_RULE_h