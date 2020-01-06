#include "Util.hpp"
#include "ExpressionTree.hpp"
#include "Rule.hpp"
#include "RuleSet.hpp"
#include <string>

using namespace std;

void statistics(shared_ptr<RuleSet> ruleSet, string filePath)
{
    ifstream file(filePath);
    if (!file)
    {
        cout << "Unable to open file\n";
        exit(1);
    }
    string str;
    shared_ptr<ExpressionTree> et;

    int changed = 0;
    int total = 0;
    map<string, string> changedRules;

    while (std::getline(file, str))
    {
        et = make_shared<ExpressionTree>(str);
        if (ruleSet->applyAllRules(et))
        {
            changed++;
            changedRules.insert(pair<string, string>(str, et->prefix()));
        }
        total++;
    }
    file.close();

    std::ofstream ofs("statistics.txt", std::ofstream::out);
    ofs << "Expressions simplified: " << changed << "/" << total << endl;

    ofs << "\nChanged expressions:\n";

    map<string, string>::iterator itr;
    for (itr = changedRules.begin(); itr != changedRules.end(); ++itr)
    {
        int diff = Util::split(itr->first, " ", true).size() - Util::split(itr->second, " ", true).size();
        string first = itr->first;
        string second = itr->second;
        ofs << first << endl;
        ofs << second << endl;
        ofs << diff << endl
            << endl;
    }

    ofs << "\n\nCnt\t\tRule used" << endl;

    for (int i = 0; i < ruleSet->getCounter().size(); i++)
    {
        ofs << ruleSet->getCounter()[i] << "\t\t" << ruleSet->getRules()[i]->printRule() << endl;
    }

    ofs.close();
}

int main()
{
    Util::loadOperators("operators.txt");

    shared_ptr<RuleSet> arithmetic = Util::loadRulesFromFile("arithmetic.txt");
    shared_ptr<RuleSet> trigonometric = Util::loadRulesFromFile("trigonometric.txt");
    shared_ptr<RuleSet> boolean_alg = Util::loadRulesFromFile("boolean.txt");

    statistics(boolean_alg, "expressions/BoolExample.txt");
}