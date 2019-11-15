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

    bool reset = true;
    vector<Rule *>::iterator itr;
    do
    {
        reset = false;
        for (int i = 0; i < rules.size(); i++)
        {
            if (rules[i]->applyRule(expression))
            {
                reset = true;
                break;
            }
        }
    } while (reset);

    cout << "Final result: ";
    expression->prefix();
    cout << "\n";
}