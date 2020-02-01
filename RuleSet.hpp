#ifndef RULE_SET_h
#define RULE_SET_h

#include "Rule.hpp"
#include "ExpressionTree.hpp"

#include <vector>

class RuleSet
{
private:
    vector<shared_ptr<Rule>> rules;
    shared_ptr<Rule> loadRule(string rule);

public:
    RuleSet(vector<shared_ptr<Rule>> rules);
    RuleSet(std::string path);

    vector<shared_ptr<Rule>> getRules();
    void addRule(shared_ptr<Rule> rule);
    shared_ptr<Rule> getRule(int index);
    int size();
};

#endif // RULE_SET_h