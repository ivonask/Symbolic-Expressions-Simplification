#include "Util.hpp"
#include "ExpressionTree.hpp"
#include "Rule.hpp"
#include "RuleSet.hpp"

using namespace std;

int main()
{
    Util::loadOperators();

    RuleSet *arithmetic = Util::loadRulesFromFile("arithmetic.txt");
    RuleSet *trigonometric = Util::loadRulesFromFile("trigonometric.txt");
    RuleSet *boolean_alg = Util::loadRulesFromFile("boolean.txt");

    // ExpressionTree *et = Util::loadExpressionFromFile("expressions.txt");
    // arithmetic->applyAllRules(et);
    //boolean_alg->applyAllRules(et);

    ifstream file("inputLogs/Pareto/extracted.txt");
    if (!file)
    {
        cout << "Unable to open file\n";
        exit(1);
    }
    string str;
    ExpressionTree *et;
    int changed = 0;
    int total = 0;
    while (std::getline(file, str))
    {
        et = new ExpressionTree(str);
        if (arithmetic->applyAllRules(et))
            changed++;
        delete et;
        total++;
    }
    file.close();

    printf("\nExpressions simplified: %d/%d\n", changed, total);
}