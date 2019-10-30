#include "ExpressionTree.hpp"
#include "Util.hpp"

#include <map>

using namespace std;

//string example from ECF:      + X sin * X 1

ExpressionTree::ExpressionTree()
{
    top = NULL;
}

ExpressionTree::ExpressionTree(Node *root)
{
    top = new StackNode(root);
}

ExpressionTree::ExpressionTree(string prefixExpression)
{
    top = NULL;
    vector<string> splitted = Util::split(prefixExpression, " ");
    buildTree(splitted);
}

void ExpressionTree::clear()
{
    top = NULL;
}

void ExpressionTree::push(Node *ptr)
{
    if (top == NULL)
        top = new StackNode(ptr);
    else
    {
        StackNode *nptr = new StackNode(ptr);
        nptr->next = top;
        top = nptr;
    }
}

Node *ExpressionTree::pop()
{
    if (top == NULL)
    {
        cout << "Underflow" << endl;
        return nullptr;
    }
    else
    {
        Node *ptr = top->node;
        top = top->next;
        return ptr;
    }
}

Node *ExpressionTree::peek()
{
    return top->node;
}

void ExpressionTree::insert(string val)
{
    if (isSymbol(val))
    {
        Node *nptr = new Node(val);
        push(nptr);
    }
    else if (isOperator(val))
    {
        Node *nptr = new Node(val);
        nptr->l = pop();
        nptr->r = pop();
        push(nptr);
    }
    else
    {
        cout << "Invalid Expression" << endl;
        return;
    }
}

// bool isConstant(string ch)
// {
//     return ch._Starts_with("_D");
// }

bool ExpressionTree::isSymbol(string ch)
{
    return (!isConstant(ch) && !isOperator(ch)); //TODO check defined variables from ECF file.
}

//     bool isDigit(char ch) {
//       return ch >= '0' && ch <= '9';
//    }

bool ExpressionTree::isOperator(string ch)
{
    return ch == "+" || ch == "-" || ch == "*" || ch == "/"; //TODO check defined operators from ECF file.
}

bool ExpressionTree::isConstant(string ch)
{
    if (ch.find("D_") == 0)
    {
        return true;
    }
    return false;
}

// int toDigit(string ch)
// {
//     return ch - "0";
// }

void ExpressionTree::buildTree(vector<string> eqn)
{
    for (auto i = eqn.rbegin(); i != eqn.rend(); ++i)
    {
        insert(eqn.back());
        eqn.pop_back();
    }
}

void ExpressionTree::translateNode(Node *n, map<string, Node *> variables)
{
    if (n == nullptr)
    {
        return;
    }
    Node *newNode;

    if (isSymbol(n->d))
    {
        //find in map, replace

        std::map<string, Node *>::iterator it = variables.find(n->d);

        //newNode = new Node(it->second);
        newNode = (it->second);
    }
    else
    {
        newNode = n;
    }

    n->d = newNode->d;

    translateNode(n->l, variables);
    translateNode(n->r, variables);
}

ExpressionTree *ExpressionTree::translate(map<string, Node *> variables)
{
    ExpressionTree *translatedTree;
    if (isSymbol(top->node->d))
    {
        //find in map, replace

        std::map<string, Node *>::iterator it = variables.find(top->node->d);

        translatedTree = new ExpressionTree(it->second);
    }
    else
    {
        translatedTree = new ExpressionTree(top->node);
    }

    translateNode(translatedTree->top->node->l, variables);
    translateNode(translatedTree->top->node->r, variables);

    return translatedTree;
}

void ExpressionTree::infix()
{
    inOrder(peek());
}

void ExpressionTree::inOrder(Node *ptr)
{
    if (ptr != NULL)
    {
        inOrder(ptr->l);
        printf("%s", ptr->d.c_str());
        inOrder(ptr->r);
    }
}
void ExpressionTree::prefix()
{
    preOrder(peek());
}

void ExpressionTree::preOrder(Node *ptr)
{
    if (ptr != NULL)
    {
        printf("%s", ptr->d.c_str());
        preOrder(ptr->l);
        preOrder(ptr->r);
    }
}
