#ifndef EXPRESSION_TREE_h
#define EXPRESSION_TREE_h

#include <vector>
#include <map>

#include "StackNode.hpp"
#include "Node.hpp"

class ExpressionTree
{
private:
    //Node *root;

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
    static bool isSymbol(string ch);
    static bool isOperator(string ch);
    static bool isConstant(string ch);

    void buildTree(vector<string> eqn);

    ExpressionTree *translate(map<string, Node *> variables);
    void translateNode(Node *n, map<string, Node *> variables);

    void infix();
    void inOrder(Node *ptr);

    string prefix();
    string preOrder(Node *ptr);
};

#endif // EXPRESSION_TREE_h