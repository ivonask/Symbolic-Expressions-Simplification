#include "Util.hpp"
#include "ExpressionTree.hpp"
#include "Rule.hpp"
#include "RuleSet.hpp"
#include <string>
#include "Simplifier.hpp"

using namespace std;

void statistics(shared_ptr<Simplifier> simplifier, string filePath)
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
    map<string, string> changedExpressions;
    map<string, string> reducedOnly;
    vector<string> notChanged;

    while (std::getline(file, str))
    {
        et = make_shared<ExpressionTree>(str);
        if (simplifier->simplify(et))
        {
            changed++;
            changedExpressions.insert(pair<string, string>(str, et->prefix()));
        }
        else if (str != et->prefix())
        {
            changed++;
            reducedOnly.insert(pair<string, string>(str, et->prefix()));
        }
        else
        {
            notChanged.push_back(et->prefix());
        }
        total++;
    }
    file.close();

    std::ofstream ofs("statistics.txt", std::ofstream::out);
    ofs << "Expressions simplified: " << changed << "/" << total << endl;
    if (!changedExpressions.empty())
    {
        ofs << "\nRules successfully applied to:\n";
        map<string, string>::iterator itr;
        for (itr = changedExpressions.begin(); itr != changedExpressions.end(); ++itr)
        {
            string first = itr->first;
            string second = itr->second;
            double diff = (1 - ((double)Util::getNoTokens(second) / (double)Util::getNoTokens(first))) * 100;
            ofs << first << endl;
            ofs << second << endl;
            ofs << "Shortened by " << diff << "%" << endl
                << endl;
        }
    }
    if (!reducedOnly.empty())
    {

        ofs << "\nExpressions where only the constants are reduced:\n";
        map<string, string>::iterator itr;
        for (itr = reducedOnly.begin(); itr != reducedOnly.end(); ++itr)
        {
            string first = itr->first;
            string second = itr->second;
            double diff = (1 - ((double)Util::getNoTokens(second) / (double)Util::getNoTokens(first))) * 100;
            ofs << first << endl;
            ofs << second << endl;
            ofs << "Shortened by " << diff << "%" << endl
                << endl;
        }
    }

    if (!notChanged.empty())
    {
        ofs << "\nExpressions not changed:\n";
        for (int i = 0; i < notChanged.size(); i++)
        {
            ofs << notChanged[i] << endl;
        }
    }
    ofs << "\n\nCnt\t\tRule used" << endl;

    for (int i = 0; i < simplifier->getCounter().size(); i++)
    {
        ofs << simplifier->getCounter()[i] << "\t\t" << simplifier->getRules()->getRule(i)->printRule() << endl;
    }

    ofs.close();
}

int main()
{
    shared_ptr<Simplifier> simplifier = make_shared<Simplifier>("ruleSets\\arithm_trig.txt", "operators.txt");

    statistics(simplifier, "expressions/offlineSinX.txt");
}