#ifndef NODE_h
#define NODE_h

#include <iostream>

using namespace std;

class Node /*node declaration*/
{
public:
    string d;
    Node *l, *r;
    Node(string d)
    {
        this->d = d;
        this->l = NULL;
        this->r = NULL;
    }
};

#endif // NODE_h