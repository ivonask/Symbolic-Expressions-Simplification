#ifndef EXPRESSION_TREE_h
#define EXPRESSION_TREE_h

#include <vector>

#include "StackNode.hpp"
#include "Node.hpp"

class ExpressionTree
{
private:
    Node *root;

public:
    StackNode *top;
    ExpressionTree();
    ExpressionTree(Node *root);
    ExpressionTree(string prefixExpression);
    void clear();

    void push(Node *ptr);
    Node *pop();
    Node *peek();

    void insert(string val);
    bool isSymbol(string ch);
    bool isOperator(string ch);

    void buildTree(vector<string> eqn);

    void infix();
    void inOrder(Node *ptr);

    void prefix();
    void preOrder(Node *ptr);
};

#endif // EXPRESSION_TREE_h