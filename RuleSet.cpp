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

shared_ptr<Rule> RuleSet::getRule(int index)
{
    return rules[index];
}

int RuleSet::size()
{
    return rules.size();
}