#ifndef RULE_SET_h
#define RULE_SET_h

#include "Rule.hpp"
#include "ExpressionTree.hpp"

#include <vector>

class RuleSet
{
private:
    vector<shared_ptr<Rule>> rules;
    vector<int> counter;

public:
    RuleSet();
    RuleSet(vector<shared_ptr<Rule>> rules);

    vector<shared_ptr<Rule>> getRules();
    vector<int> getCounter();
    void addRule(shared_ptr<Rule> rule);
    int applyAllRules(shared_ptr<ExpressionTree> expression);
};

#endif // RULE_SET_h