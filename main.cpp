#include "Util.hpp"
#include "ExpressionTree.hpp"
#include "Rule.hpp"

using namespace std;

void print(ExpressionTree *et)
{
    cout << "Prefix : ";
    et->prefix();
    cout << "\nInfix : ";
    et->infix();
    cout << "\n\n";
}

int main()
{
    string original = "* X + Y Z";        // X(Y+Z)
    string replacement = "+ * X Y * X Z"; //XY+XZ
    Rule *r1 = new Rule(original, replacement);

    Rule *r2 = new Rule("+ X X", "* D_2 X");

    Rule *r3 = new Rule("* X D_1", "X");

    //string s = "+ + X * Y Z Y";
    ExpressionTree *et1 = new ExpressionTree("* * x1 x2 + * y1 y2 z");

    //r1->applyRule(et1);

    ExpressionTree *et4 = new ExpressionTree("+ a a");
    //r2->applyRule(et4);

    ExpressionTree *et5 = new ExpressionTree("+ a D_1");
    //r3->applyRule(et5);

    //(x1+x1)*x2(y1*y2+z*D_1)
    ExpressionTree *et6 = new ExpressionTree("* * + x1 x1 x2 + * y1 y2 * z D_1");
    print(et6);

    r1->applyRule(et6);
    print(et6);

    r2->applyRule(et6);
    print(et6);

    r3->applyRule(et6);
    print(et6);
}