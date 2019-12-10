#ifndef RULE_SET_h
#define RULE_SET_h

#include "Rule.hpp"
#include "ExpressionTree.hpp"

#include <vector>

class RuleSet
{
private:
    vector<Rule *> rules;
    vector<int> counter;

public:
    RuleSet();
    RuleSet(vector<Rule *> rules);

    vector<Rule *> getRules();
    vector<int> getCounter();
    void addRule(Rule *rule);
    int applyAllRules(ExpressionTree *expression);
};

#endif // RULE_SET_h