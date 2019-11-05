#include "Util.hpp"
#include "ExpressionTree.hpp"
#include "Rule.hpp"

using namespace std;

int main()
{
    string original = "* X + Y Z";        // X(Y+Z)
    string replacement = "+ * X Y * X Z"; //XY+XZ
    Rule *r1 = new Rule(original, replacement);

    Rule *r2 = new Rule("+ X X", "* D_2 X");

    //string s = "+ + X * Y Z Y";
    ExpressionTree *et = new ExpressionTree("+ c + * a + b c b");
    ExpressionTree *et1 = new ExpressionTree("* * x1 x2 + * y1 y2 z");
    ExpressionTree *et2 = new ExpressionTree("* x + * y1 y2 z");
    ExpressionTree *et3 = new ExpressionTree("* x + y * z w");

    ExpressionTree *et4 = new ExpressionTree("+ a a");

    r2->applyRule(et4);

    cout << "Prefix : ";
    et4->prefix();
    cout << "\nInfix : ";
    et4->infix();
    cout << "\n";
}