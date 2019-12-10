#include "Operator.hpp"

OperatorNode::OperatorNode(string name, int childrenNumber)
{
    this->op = name;
    this->childrenNumber = childrenNumber;
}

int OperatorNode::numberOfChildren()
{
    return childrenNumber;
}

//string OperatorNode::print(vector<string> children)
//{
//}