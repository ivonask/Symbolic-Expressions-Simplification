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

ExpressionTree::ExpressionTree(shared_ptr<Node> root)
{
    top = make_shared<StackNode>(root);
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

void ExpressionTree::push(shared_ptr<Node> ptr)
{
    if (top == NULL)
        top = make_shared<StackNode>(ptr);
    else
    {
        shared_ptr<StackNode> nptr = make_shared<StackNode>(ptr);
        nptr->next = top;
        top = nptr;
    }
}

shared_ptr<Node> ExpressionTree::pop()
{
    if (top == NULL)
    {
        cout << "Underflow" << endl;
        return nullptr;
    }
    else
    {
        shared_ptr<Node> ptr = top->node;
        top = top->next;
        return ptr;
    }
}

shared_ptr<Node> ExpressionTree::peek()
{
    return top->node;
}

void ExpressionTree::insert(string val)
{
    if (isSymbol(val) || isConstant(val))
    {
        shared_ptr<Node> nptr = make_shared<Node>(val);
        push(nptr);
    }
    else if (isOperator(val))
    {
        shared_ptr<Node> nptr = make_shared<Node>(val);

        shared_ptr<OperatorNode> op = Util::getOperatorInfo(val);

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
    for (int i = eqn.size() - 1; i >= 0; i--)
        insert(eqn[i]);
}

void ExpressionTree::translateNode(shared_ptr<Node> n, map<string, shared_ptr<Node>> variables)
{
    if (n == nullptr)
    {
        return;
    }

    if (isSymbol(n->d))
    {
        //find in map, replace

        std::map<string, shared_ptr<Node>>::iterator it = variables.find(n->d);
        if (it == variables.end())
            return;

        //newNode = new Node(it->second);
        shared_ptr<Node> newNode(it->second);
        *n = *newNode;
    }

    for (int i = 0; i < n->chlidren.size(); i++)
        translateNode(n->chlidren[i], variables);
}

shared_ptr<ExpressionTree> ExpressionTree::translate(map<string, shared_ptr<Node>> variables)
{
    shared_ptr<ExpressionTree> translatedTree;
    if (isSymbol(top->node->d))
    {
        //find in map, replace

        std::map<string, shared_ptr<Node>>::iterator it = variables.find(top->node->d);

        translatedTree = make_shared<ExpressionTree>(it->second);
    }
    else
    {
        translatedTree = make_shared<ExpressionTree>(top->node);
    }

    for (int i = 0; i < translatedTree->top->node->chlidren.size(); i++)
        translateNode(translatedTree->top->node->chlidren[i], variables);

    return translatedTree;
}

void ExpressionTree::infix()
{
    inOrder(peek());
}

void ExpressionTree::inOrder(shared_ptr<Node> ptr)
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
string ExpressionTree::prefix()
{
    return preOrder(peek());
}

void replaceAll(std::string &str, const std::string &from, const std::string &to)
{
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

string ExpressionTree::preOrder(shared_ptr<Node> ptr)
{
    if (ptr != NULL)
    {
        string res = "";
        res = res + ptr->d + " ";
        if (!ptr->chlidren.empty())
        {
            for (int i = 0; i < ptr->chlidren.size(); i++)
                res = res + preOrder(ptr->chlidren[i]) + " ";
        }

        while (res.find("  ") != std::string::npos)
        {
            replaceAll(res, "  ", " "); //replaces double spaces with one
        }

        return res;
    }
    return NULL;
}
