#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>

#include "Util.hpp"
#include "ExpressionTree.hpp"

using namespace std;

int main()
{
    string s = "+ + X * Y Z Y";
    ExpressionTree *et = new ExpressionTree(s);
    cout << "Prefix : ";
    et->prefix();
    cout << "\nInfix : ";
    et->infix();
}