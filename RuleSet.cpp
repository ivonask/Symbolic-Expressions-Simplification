#include "RuleSet.hpp"

RuleSet::RuleSet(vector<Rule *> rules)
{
    this->rules = rules;
}

void RuleSet::addRule(Rule *rule)
{
    rules.push_back(rule);
}
void RuleSet::applyAllRules(ExpressionTree *expression)
{
    cout << "\nInitial expression: ";
    expression->prefix();
    cout << "\n";

    vector<Rule *>::iterator itr;
    for (int i = 0; i < rules.size(); i++)
    {
        rules[i]->applyRule(expression);
    }

    cout << "Final result: ";
    expression->prefix();
    cout << "\n";
}