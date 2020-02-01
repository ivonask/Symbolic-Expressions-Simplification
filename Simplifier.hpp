#ifndef SIMPLIFIER_h
#define SIMPLIFIER_h

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include <memory>

#include "Operator.hpp"
#include "Node.hpp"
#include "RuleSet.hpp"

using namespace std;

class Simplifier
{
protected:
    static vector<string> operators;
    static map<string, shared_ptr<OperatorNode>> operatorsInfo;

    shared_ptr<RuleSet> rules;
    vector<int> counter;

public:
    Simplifier(string rulesPath, string operatorsPath);
    Simplifier();

    static void loadOperators(string file_in);
    static void loadOperators(map<string, int> ops);

    void setRules(shared_ptr<RuleSet> rules);
    shared_ptr<RuleSet> getRules();
    int simplify(shared_ptr<ExpressionTree> tree);

    static bool isOperatorLoaded(string name);
    static shared_ptr<OperatorNode> getOperatorInfo(string name);

    bool reduceConstants(shared_ptr<Node> n);
    vector<int> getCounter();
};

#endif // SIMPLIFIER_h