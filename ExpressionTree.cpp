#include "ExpressionTree.hpp"

using namespace std;

//string example from ECF:      + X sin * X 1

    ExpressionTree::ExpressionTree()
    {
        top = NULL;
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
        return ch == "X" || ch == "Y" || ch == "Z";
    }

    //     bool isDigit(char ch) {
    //       return ch >= '0' && ch <= '9';
    //    }

    bool ExpressionTree::isOperator(string ch)
    {
        return ch == "+" || ch == "-" || ch == "*" || ch == "/";
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
