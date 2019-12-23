#ifndef REWRITE_RULE_h
#define REWRITE_RULE_h

#include <map>

#include "ExpressionTree.hpp"

class Rule
{
private:
    shared_ptr<ExpressionTree> original, replacement;
    string originalStr, replacementStr;
    map<string, shared_ptr<Node>> variables;

    bool match(shared_ptr<Node> P, shared_ptr<Node> T);
    bool compare(shared_ptr<Node> P, shared_ptr<Node> U);

    bool isAddedToMap(string var, shared_ptr<Node> n);
    bool compareNode(shared_ptr<Node> n1, shared_ptr<Node> n2);

public:
    Rule(string original, string replacement);
    bool applyRule(shared_ptr<ExpressionTree> expression);
    string printRule();
};

#endif // REWRITE_RULE_h