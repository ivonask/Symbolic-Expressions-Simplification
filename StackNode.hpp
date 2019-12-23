#ifndef STACK_NODE_h
#define STACK_NODE_h

#include "Node.hpp"

using namespace std;

class StackNode /*stack declaration */
{
public:
    shared_ptr<Node> node;
    shared_ptr<StackNode> next;
    StackNode(shared_ptr<Node> treeN)
    {
        this->node = treeN;
        next = NULL;
    }
};

#endif // STACK_NODE_h