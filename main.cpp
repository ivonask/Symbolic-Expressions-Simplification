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

    ExpressionTree *et = Util::loadExpressionFromFile("expressions.txt");
    arithmetic->applyAllRules(et);
}