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
    Rule *r6 = new Rule(replacement, original);

    Rule *r2 = new Rule("+ X X", "* D_2 X");

    Rule *r3 = new Rule("* X D_1", "X");

    Rule *r4 = new Rule("* X D_0", "D_0");

    Rule *r5 = new Rule("+ D_0 X", "X");

    //string s = "+ + X * Y Z Y";
    ExpressionTree *et1 = new ExpressionTree("* * x1 x2 + * y1 y2 z");
    //r1->applyRule(et1);

    ExpressionTree *et4 = new ExpressionTree("+ a a");
    //r2->applyRule(et4);

    ExpressionTree *et5 = new ExpressionTree("+ a D_1");
    //r3->applyRule(et5);

    //(x1+x1)*x2*(y1*y2+z*D_1)
    ExpressionTree *et6 = new ExpressionTree("* * + x1 x1 x2 + * y1 y2 * z D_1");
    //print(et6);

    //(x1+x1)*x2*(y1*y2+z*D_1)*D_0
    //ExpressionTree *et7 = new ExpressionTree("* * * + x1 x1 x2 + * y1 y2 * z D_1 D_0");   //works
    //(x1+x1)*x2*(y1*y2*D_0+z*D_1)
    // ExpressionTree *et7 = new ExpressionTree("* * + x1 x1 x2 + * * y1 y2 D_0 * z D_1"); //works
    // print(et7);

    // r4->applyRule(et7);
    // print(et7);

    // r5->applyRule(et7);
    // print(et7);

    // r1->applyRule(et7);
    // print(et7);

    // r3->applyRule(et7);
    // print(et7);

    // r2->applyRule(et7);
    // print(et7);

    //((a * b + c * d * e) * y + (a * b + c * d * e) * z) * A + C * (x * y + x * z) * B
    // ExpressionTree *et8 = new ExpressionTree("+ * + * + * a b * * c d e y * + * a b * * c d e z A * * C + * x y * x z D_0"); //works
    // print(et8);

    // r6->applyRule(et8);
    // print(et8);

    // r4->applyRule(et8);
    // print(et8);

    ExpressionTree *et9 = new ExpressionTree("+ * + * a b * * c d e y * + * a b * * c d e z"); //works
    print(et9);

    r6->applyRule(et9);
    print(et9);
}