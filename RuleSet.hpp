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
	shared_ptr<Rule> loadRule(string rule);

public:
    RuleSet(vector<shared_ptr<Rule>> rules);
	RuleSet(std::string path);

    vector<shared_ptr<Rule>> getRules();
    vector<int> getCounter();
    void addRule(shared_ptr<Rule> rule);
    int applyAllRules(shared_ptr<ExpressionTree> expression);
};

#endif // RULE_SET_h