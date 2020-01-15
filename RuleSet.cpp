#include "RuleSet.hpp"
#include "Util.hpp"
#include <string>

int MAX_ITERATIONS = 50;

RuleSet::RuleSet(vector<shared_ptr<Rule>> rules)
{
    this->rules = rules;
}

RuleSet::RuleSet(std::string path)
{
    vector<shared_ptr<Rule>> rules;
    ifstream file(path);
    if (!file)
    {
        cout << "Unable to open file " << path;
        return;
    }
    string str;
    while (std::getline(file, str))
    {
        rules.push_back(loadRule(str));
    }
    file.close();
    this->rules = rules;
}

shared_ptr<Rule> RuleSet::loadRule(string rule)
{
    vector<string> ruleVec = Util::split(rule, "->", true);
    return make_shared<Rule>(ruleVec[0], ruleVec[1]);
}

void RuleSet::addRule(shared_ptr<Rule> rule)
{
    rules.push_back(rule);
}

vector<shared_ptr<Rule>> RuleSet::getRules()
{
    return rules;
}

vector<int> RuleSet::getCounter()
{
    return counter;
}

int RuleSet::applyAllRules(shared_ptr<ExpressionTree> expression)
{
    if (counter.empty())
    {
        for (int i = 0; i < rules.size(); i++)
        {
            counter.push_back(0);
        }
    }

    cout << "\nInitial expression: ";
    cout << expression->prefix().c_str();
    cout << "\n\n";

    int appliedRules = 0;

    while (Util::reduceConstants(expression->peek()))
        ;

    bool reset = true;
    vector<shared_ptr<Rule>>::iterator itr;
    int cnt = 0;
    do
    {
        reset = false;

        int i = 0;
        for (i = 0; i < rules.size(); i++)
        {
            if (rules[i]->applyRule(expression))
            {
                while (Util::reduceConstants(expression->peek()))
                    cout << expression->prefix().c_str() << endl;

                cout << "New expression: ";
                cout << expression->prefix().c_str();
                cout << "\n\n";

                appliedRules++;
                counter[i]++;

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
    cout << expression->prefix().c_str();
    cout << "\n";

    return appliedRules;
}