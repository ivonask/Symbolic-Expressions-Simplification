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
    std::vector<shared_ptr<Node>> chlidren;
    Node(string d)
    {
        this->d = d;
    }
    Node(shared_ptr<Node> n)
    {
        this->d = n->d;
        this->chlidren = n->chlidren;
    }
};

#endif // NODE_h