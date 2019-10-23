#ifndef REWRITE_RULE_h
#define REWRITE_RULE_h

#include "ExpressionTree.hpp"

class Rule {
private:
    string original, replacement;

public:
    
    Rule(string original, string replacement);
    ExpressionTree applyRule(ExpressionTree expression, Rule rule);
};

#endif // REWRITE_RULE_h