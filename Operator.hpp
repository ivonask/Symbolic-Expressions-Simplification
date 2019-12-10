#ifndef OPERATOR_h
#define OPERATOR_h

#include <iostream>
#include <vector>

using namespace std;

class OperatorNode
{
private:
    string op;
    int childrenNumber;

public:
    OperatorNode(string name, int childrenNumber);
    int numberOfChildren();
    string print(vector<string> children);
};

#endif // OPERATOR_h