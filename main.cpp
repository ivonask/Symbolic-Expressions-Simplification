#include "Util.hpp"
#include "ExpressionTree.hpp"
#include "Rule.hpp"
#include "RuleSet.hpp"

using namespace std;

RuleSet *loadArithmeticRuleSet()
{
    string original = "* X + Y Z";        // X(Y+Z)
    string replacement = "+ * X Y * X Z"; //XY+XZ
    //Rule *r1 = new Rule(original, replacement);
    Rule *r6 = new Rule(replacement, original);

    Rule *r2 = new Rule("+ X X", "* D_2 X");
    Rule *r3 = new Rule("* X D_1", "X");
    Rule *r4 = new Rule("* X D_0", "D_0");
    Rule *r5 = new Rule("+ D_0 X", "X");

    vector<Rule *> vect{r2, r3, r4, r5, r6};

    return new RuleSet(vect);
}

RuleSet *loadTrigonometricRuleSet()
{
    Rule *r1 = new Rule("+ * sin A cos B * cos A sin B", "sin + A B");
    vector<Rule *> vect{r1};

    return new RuleSet(vect);
}

void loadBooleanRuleSet()
{
}

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

    RuleSet *arithmetic = loadArithmeticRuleSet();
    RuleSet *trigonometric = loadTrigonometricRuleSet();

    ExpressionTree *et1 = new ExpressionTree("+ * * * x1 x2 y1 y2 * * x1 x2 z");
    ExpressionTree *et2 = new ExpressionTree("+ a a");
    ExpressionTree *et3 = new ExpressionTree("* a D_1");

    arithmetic->applyAllRules(et1);
    arithmetic->applyAllRules(et2);
    arithmetic->applyAllRules(et3);

    //(x1+x1)*x2*y1*y2+(x1+x1)*x2*z*D_1
    ExpressionTree *et4 = new ExpressionTree("+ * * * + x1 x1 x2 y1 y2 * * * + x1 x1 x2 z D_1");

    // (x1+x1)*x2*y1*y2*D_0+(x1+x1)*x2*z*D_1
    ExpressionTree *et5 = new ExpressionTree("+ * * * * + x1 x1 x2 y1 y2 D_0 * * * + x1 x1 x2 z D_1"); //works

    arithmetic->applyAllRules(et4);
    arithmetic->applyAllRules(et5);

    // //((a * b + c * d * e) * y + (a * b + c * d * e) * z) * A + C * (x * y + x * z) * B
    ExpressionTree *et8 = new ExpressionTree("+ * + * + * a b * * c d e y * + * a b * * c d e z A * * C + * x y * x z D_0"); //works
    // printTree(et8);

    ExpressionTree *et9 = new ExpressionTree("+ * + * a b * * c d e y * + * a b * * c d e z"); //works
    // printTree(et9);

    arithmetic->applyAllRules(et8);
    arithmetic->applyAllRules(et9);

    ExpressionTree *et10 = new ExpressionTree("+ X sin * X D_1");
    // // printTree(et10);

    ExpressionTree *et12 = new ExpressionTree("+ * sin a cos b * cos a sin b");
    // //printTree(et12);

    arithmetic->applyAllRules(et10);
    trigonometric->applyAllRules(et12);

    // cout << "\n";
    // ExpressionTree *et11 = new ExpressionTree("ifpos * X1 X2 Y Z");
    // printTree(et11);
}