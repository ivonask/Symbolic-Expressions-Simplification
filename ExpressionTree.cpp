#include "ExpressionTree.hpp"
#include "Util.hpp"
#include "Operator.hpp"

#include <map>
#include <algorithm>

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
    if (isSymbol(val) || isConstant(val))
    {
        Node *nptr = new Node(val);
        push(nptr);
    }
    else if (isOperator(val))
    {
        Node *nptr = new Node(val);

        Operator *op = Util::getOperatorInfo(val);

        //TODO: read from some definition of the operator - how many children?
        //or: while pop() =! null?
        for (int i = 0; i < op->numberOfChildren(); i++)
        {
            nptr->chlidren.push_back(pop());
        }

        push(nptr);
    }
    else
    {
        cout << "Invalid Expression" << endl;
        return;
    }
}

bool ExpressionTree::isSymbol(string ch)
{
    return (!isConstant(ch) && !isOperator(ch)); //TODO check defined variables from ECF file.
}

bool ExpressionTree::isOperator(string ch)
{
    return Util::isOperatorLoaded(ch);
}

bool ExpressionTree::isConstant(string ch)
{
    if (ch.find("D_") == 0)
    {
        return true;
    }
    return false;
}

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
        if (it == variables.end())
            return;

        //newNode = new Node(it->second);
        newNode = (it->second);
    }
    else
    {
        newNode = n;
    }

    *n = *newNode;

    for (int i = 0; i < n->chlidren.size(); i++)
        translateNode(n->chlidren[i], variables);
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

    for (int i = 0; i < translatedTree->top->node->chlidren.size(); i++)
        translateNode(translatedTree->top->node->chlidren[i], variables);

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
        if (ptr->chlidren.empty())
        {
            printf("%s ", ptr->d.c_str());
        }
        else
        {
            if (ptr->chlidren.size() == 1)
            {
                printf("%s (", ptr->d.c_str());
                inOrder(ptr->chlidren[0]);
                printf(")");
            }
            else if (ptr->chlidren.size() == 2)
            {
                inOrder(ptr->chlidren[0]);
                printf("%s ", ptr->d.c_str());
                inOrder(ptr->chlidren[1]);
            }
            else
            {
                printf("%s (", ptr->d.c_str());
                for (int i = 0; i < ptr->chlidren.size(); i++)
                {
                    inOrder(ptr->chlidren[i]);
                    if (i != ptr->chlidren.size() - 1)
                        printf(",");
                }
                printf(")");
            }
        }
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
        printf("%s ", ptr->d.c_str());
        for (int i = 0; i < ptr->chlidren.size(); i++)
            preOrder(ptr->chlidren[i]);
    }
}
