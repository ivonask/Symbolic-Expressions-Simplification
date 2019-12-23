#include "Util.hpp"
#include "ExpressionTree.hpp"
#include "Rule.hpp"
#include "RuleSet.hpp"
#include <string>

using namespace std;

int main()
{
    Util::loadOperators();

    shared_ptr<RuleSet> arithmetic = Util::loadRulesFromFile("arithmetic.txt");
    shared_ptr<RuleSet> trigonometric = Util::loadRulesFromFile("trigonometric.txt");
    shared_ptr<RuleSet> boolean_alg = Util::loadRulesFromFile("boolean.txt");

    // ExpressionTree *et = Util::loadExpressionFromFile("expressions.txt");
    // arithmetic->applyAllRules(et);
    //boolean_alg->applyAllRules(et);

    ifstream file("reduceThis.txt");
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
        if (arithmetic->applyAllRules(et))
        {
            changed++;
            changedRules.insert(pair<string, string>(str, et->prefix()));
        }
        total++;
    }
    file.close();

    std::ofstream ofs("statistics.txt", std::ofstream::out);
    ofs << "Expressions simplified: " << changed << "/" << total << endl;

    ofs << "\nChanged rules:\n";

    map<string, string>::iterator itr;
    for (itr = changedRules.begin(); itr != changedRules.end(); ++itr)
    {
        int diff = Util::split(itr->first, " ").size() - Util::split(itr->second, " ").size();
        string first = itr->first;
        string second = itr->second;
        ofs << first << endl;
        ofs << second << endl;
        ofs << diff << endl
            << endl;
    }

    ofs << "\n\nCnt\t\tRule used" << endl;

    for (int i = 0; i < arithmetic->getCounter().size(); i++)
    {
        ofs << arithmetic->getCounter()[i] << "\t\t" << arithmetic->getRules()[i]->printRule() << endl;
    }

    ofs.close();
}