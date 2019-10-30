#include "Util.hpp"
#include "ExpressionTree.hpp"
#include "Rule.hpp"

using namespace std;

int main()
{
    string original = "* X + Y Z";        // X(Y+Z)
    string replacement = "+ * X Y * X Z"; //XY+XZ
    Rule *r1 = new Rule(original, replacement);

    //string s = "+ + X * Y Z Y";
    //ExpressionTree *et = new ExpressionTree("+ c + * a + b c b");
    ExpressionTree *et = new ExpressionTree("+ x + * a + b d y");

    r1->applyRule(et);

    cout << "Prefix : ";
    et->prefix();
    cout << "\nInfix : ";
    et->infix();
    cout << "\n";
}