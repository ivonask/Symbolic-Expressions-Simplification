#ifndef EXPRESSION_TREE_h
#define EXPRESSION_TREE_h

#include <vector>
#include <map>
#include <memory>

#include "StackNode.hpp"
#include "Node.hpp"

using namespace std;

class ExpressionTree
{
private:
    //Node *root;

public:
    shared_ptr<StackNode> top;
    ExpressionTree();
    ExpressionTree(shared_ptr<Node> root);
    ExpressionTree(string prefixExpression);
    void clear();

    void push(shared_ptr<Node> ptr);
    shared_ptr<Node> pop();
    shared_ptr<Node> peek();

    void insert(string val);
    static bool isSymbol(string ch);
    static bool isOperator(string ch);
    static bool isConstant(string ch);

    void buildTree(vector<string> eqn);

    shared_ptr<ExpressionTree> translate(map<string, shared_ptr<Node>> variables);
    void translateNode(shared_ptr<Node> n, map<string, shared_ptr<Node>> variables);

    void infix();
    void inOrder(shared_ptr<Node> ptr);

    string prefix();
    string preOrder(shared_ptr<Node> ptr);
};

#endif // EXPRESSION_TREE_h