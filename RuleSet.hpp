#ifndef RULE_SET_h
#define RULE_SET_h

#include "Rule.hpp"
#include "ExpressionTree.hpp"

#include <vector>

class RuleSet
{
private:
    vector<Rule *> rules;

public:
    RuleSet();
    RuleSet(vector<Rule *> rules);

    void addRule(Rule *rule);
    void applyAllRules(ExpressionTree *expression);
};

#endif // RULE_SET_h