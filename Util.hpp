#ifndef UTIL_h
#define UTIL_h

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include <memory>

#include "Operator.hpp"
#include "Rule.hpp"
#include "RuleSet.hpp"
#include "ExpressionTree.hpp"

using namespace std;

class Util
{
public:
    static vector<string> split(const string &str, const string &delim, bool transformConstants);

    static void printTree(shared_ptr<ExpressionTree> et);
    static int getNoTokens(string expression);
};

#endif // UTIL_h