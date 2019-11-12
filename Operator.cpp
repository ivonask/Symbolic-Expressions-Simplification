#include "Operator.hpp"

Operator::Operator(string name, int childrenNumber)
{
    this->op = name;
    this->childrenNumber = childrenNumber;
}

int Operator::numberOfChildren()
{
    return childrenNumber;
}

string Operator::print(vector<string> children)
{
}