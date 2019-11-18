#include "RuleSet.hpp"

int MAX_ITERATIONS = 4;

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
    cout << "\n\n";

    bool reset = true;
    vector<Rule *>::iterator itr;
    int ruleAppliedBefore = rules.size(); //anti infinite loop mechanism
    int cnt = 0;
    do
    {
        reset = false;

        int i = 0;
        for (i = 0; i < rules.size(); i++)
        {
            if (rules[i]->applyRule(expression))
            {
                cout << "New expression: ";
                expression->prefix();
                cout << "\n\n";

                reset = true;
                break;
            }
        }
        if (ruleAppliedBefore == i && ++cnt >= MAX_ITERATIONS - 1)
        {
            reset = false;
        }
        else if (ruleAppliedBefore != i)
        {
            cnt = 0;
        }
        ruleAppliedBefore = i;
    } while (reset);

    cout << "Final result: ";
    expression->prefix();
    cout << "\n";
}