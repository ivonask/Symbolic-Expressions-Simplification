#include "RuleSet.hpp"

int MAX_ITERATIONS = 50;

RuleSet::RuleSet(vector<Rule *> rules)
{
    this->rules = rules;
}

void RuleSet::addRule(Rule *rule)
{
    rules.push_back(rule);
}
int RuleSet::applyAllRules(ExpressionTree *expression)
{
    cout << "\nInitial expression: ";
    expression->prefix();
    cout << "\n\n";

    int appliedRules = 0;

    bool reset = true;
    vector<Rule *>::iterator itr;
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

                appliedRules++;

                reset = true;
                break;
            }
        }
        if (cnt >= MAX_ITERATIONS)
        {
            cnt = 0;
            reset = true;
        }
        cnt++;
    } while (reset);

    cout << "Final result: ";
    expression->prefix();
    cout << "\n";

    return appliedRules;
}