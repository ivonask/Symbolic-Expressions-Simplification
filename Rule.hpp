#ifndef REWRITE_RULE_h
#define REWRITE_RULE_h

#include <map>

#include "ExpressionTree.hpp"

class Rule
{
private:
    ExpressionTree *original, *replacement;
    std::map<string, Node *> variables;

    void match(Node *P, Node *T);
    bool compare(Node *P, Node *U);

    bool isAddedToMap(string var, Node *n);
    bool compareNode(Node *n1, Node *n2);

public:
    Rule(string original, string replacement);
    void applyRule(ExpressionTree *expression);
};

#endif // REWRITE_RULE_h