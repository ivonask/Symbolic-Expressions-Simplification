#include "Util.hpp"
#include "ExpressionTree.hpp"
#include "Rule.hpp"
#include "RuleSet.hpp"

using namespace std;

void printTree(ExpressionTree *et)
{
    cout << "Prefix : ";
    et->prefix();
    cout << "\nInfix : ";
    et->infix();
    cout << "\n\n";
}

int main()
{
    Util::loadOperators();

    RuleSet *arithmetic = Util::loadRulesFromFile("arithmetic.txt");
    RuleSet *trigonometric = Util::loadRulesFromFile("trigonometric.txt");

    ExpressionTree *et1 = new ExpressionTree("+ * * x1 x2 y * * x1 x2 z");
    ExpressionTree *et2 = new ExpressionTree("+ a a");
    ExpressionTree *et3 = new ExpressionTree("* a D_1");

    arithmetic->applyAllRules(et1);
    arithmetic->applyAllRules(et2);
    arithmetic->applyAllRules(et3);

    //(x1+x1)*x2*y1*y2+(x1+x1)*x2*z*D_1
    ExpressionTree *et4 = new ExpressionTree("+ * * * + x1 x1 x2 y1 y2 * * * + x1 x1 x2 z D_1");

    // (x1+x1)*x2*y1*y2*D_0+(x1+x1)*x2*z*D_1
    ExpressionTree *et5 = new ExpressionTree("+ * * * * + x1 x1 x2 y1 y2 D_0 * * * + x1 x1 x2 z D_1");

    arithmetic->applyAllRules(et4);
    arithmetic->applyAllRules(et5);

    // //((a * b + c * d * e) * y + (a * b + c * d * e) * z) * A + C * (x * y + x * z) * B
    ExpressionTree *et8 = new ExpressionTree("+ * + * + * a b * * c d e y * + * a b * * c d e z A * * C + * x y * x z D_0");
    ExpressionTree *et9 = new ExpressionTree("+ * + * a b * * c d e y * + * a b * * c d e z");

    arithmetic->applyAllRules(et8);
    arithmetic->applyAllRules(et9);

    ExpressionTree *et10 = new ExpressionTree("+ X sin * X D_1");
    ExpressionTree *et12 = new ExpressionTree("+ * sin a cos b * cos a sin b");

    arithmetic->applyAllRules(et10);
    trigonometric->applyAllRules(et12);

    // cout << "\n";
    // ExpressionTree *et11 = new ExpressionTree("ifpos * X1 X2 Y Z");
    // printTree(et11);
}