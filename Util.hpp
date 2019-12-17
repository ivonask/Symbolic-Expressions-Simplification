#ifndef UTIL_h
#define UTIL_h

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>

#include "Operator.hpp"
#include "Rule.hpp"
#include "RuleSet.hpp"
#include "ExpressionTree.hpp"

using namespace std;

class Util
{
private:
    static vector<string> operators;
    static map<string, OperatorNode *> operatorsInfo;
    static Rule *loadRule(string rule);

public:
    static vector<string> split(const string &str, const string &delim);

    static bool isOperatorLoaded(string name);
    static OperatorNode *getOperatorInfo(string name);
    static void loadOperators();

    static RuleSet *loadRulesFromFile(string file_in);
    static ExpressionTree *loadExpressionFromFile(string file_in);

    static void printTree(ExpressionTree *et);

    static bool reduceConstants(Node *n);
};

#endif // UTIL_h