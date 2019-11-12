#ifndef OPERATOR_h
#define OPERATOR_h

#include <iostream>
#include <vector>

using namespace std;

class Operator
{
private:
    string op;
    int childrenNumber;

public:
    Operator(string name, int childrenNumber);
    int numberOfChildren();
    string print(vector<string> children);
};

#endif // OPERATOR_h