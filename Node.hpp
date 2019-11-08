#ifndef NODE_h
#define NODE_h

#include <iostream>
#include <map>
#include <memory>

//#include "ExpressionTree.hpp"

using namespace std;

class Node /*node declaration*/
{
public:
    string d;
    std::vector<Node *> chlidren;
    Node(string d)
    {
        this->d = d;
    }
    Node(Node *n)
    {
        this->d = n->d;
        this->chlidren = n->chlidren;
    }
};

#endif // NODE_h