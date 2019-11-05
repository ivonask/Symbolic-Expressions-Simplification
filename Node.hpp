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
    std::vector<Node*> chlidren;
    Node(string d)
    {
        this->d = d;
    }
    Node(Node *n)
    {
        this->d = n->d;
        this->chlidren = n->chlidren;
    }

    // void translateNode(map<string, Node *> variables)
    // {
    //     if (this == nullptr)
    //     {
    //         return;
    //     }
    //     Node *newNode;

    //     if (ExpressionTree::isSymbol(this->d))
    //     {
    //         //find in map, replace

    //         std::map<string, Node *>::iterator it = variables.find(this->d);

    //         newNode = new Node(it->second);
    //     }
    //     else
    //     {
    //         newNode = this;
    //     }

    //     this->d = newNode->d;

    //     translateNode(variables);
    //     translateNode(variables);
    // }
};

#endif // NODE_h