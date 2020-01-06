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
private:
    static vector<string> operators;
    static map<string, shared_ptr<OperatorNode>> operatorsInfo;
    static shared_ptr<Rule> loadRule(string rule);

public:
    static vector<string> split(const string &str, const string &delim, bool transformConstants);

    static bool isOperatorLoaded(string name);
    static shared_ptr<OperatorNode> getOperatorInfo(string name);
    static void loadOperators(string file_in);

    static shared_ptr<RuleSet> loadRulesFromFile(string file_in);
    static shared_ptr<ExpressionTree> loadExpressionFromFile(string file_in);

    static void printTree(shared_ptr<ExpressionTree> et);

    static bool reduceConstants(shared_ptr<Node> n);
};

#endif // UTIL_h