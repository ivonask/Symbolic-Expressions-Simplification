#ifndef STACK_NODE_h
#define STACK_NODE_h

#include "Node.hpp"

class StackNode /*stack declaration */
{
public:
    Node *node;
    StackNode *next;
    StackNode(Node *treeN)
    {
        this->node = treeN;
        next = NULL;
    }
};

#endif // STACK_NODE_h