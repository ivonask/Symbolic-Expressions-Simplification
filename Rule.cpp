#include "Rule.hpp"

std::map<string, Node *> variables;

Rule::Rule(string original, string replacement)
{
    this->original = new ExpressionTree(original);
    this->replacement = new ExpressionTree(replacement);
}

bool Rule::isAddedToMap(string var, Node *n)
{
    std::map<string, Node *>::iterator it = variables.find(var);
    if (it == variables.end())
    {
        variables.insert(pair<string, Node *>(var, n));
        return true;
    }
    else if (variables.find(var)->second->d == n->d)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Rule::compareNode(Node *n1, Node *n2)
{
    //case 1: both nodes operators
    if (ExpressionTree::isOperator(n1->d) && ExpressionTree::isOperator(n2->d))
    {
        if (n1->d == n2->d)
            return true;
        else
            return false;
    }
    //case 2: pattern node is a variable/constant, expression node is an operator -> expression subtree is represented as that pattern variable, if constant return false
    else if (ExpressionTree::isOperator(n2->d))
    {
        if (ExpressionTree::isConstant(n1->d))
            return false;
        else
        {
            return isAddedToMap(n1->d, n2);
        }
    }
    //case 3: expression node is a variable/constant, pattern node is an operator
    else if (ExpressionTree::isOperator(n1->d))
    {
        return false;
    }
    //case 5: both nodes are variables/constants
    else
    {
        return isAddedToMap(n1->d, n2);
    }
}

void Rule::applyRule(ExpressionTree *expression)
{
    //ExpressionTree *result;

    match(original->peek(), expression->peek());

    //return result;
}

void printMap()
{
    std::map<string, Node *>::iterator itr;
    cout << "\nThe variables dictionary is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = variables.begin(); itr != variables.end(); ++itr)
    {
        cout << '\t' << itr->first
             << '\t' << itr->second->d << '\n';
    }
    cout << endl;
}

void Rule::match(Node *P, Node *T)
{
    if (compare(P, T))
    {
        cout << "Found a pattern!\n";

        //replace the original tree with replacement tree
        //*T = *replacement->peek();

        cout << replacement->peek()->d;

        // std::map<string, Node *>::iterator it = variables.find(replacement->peek()->d);

        // cout << it->second->d;

        // Node *n = it->second;

        // *T = *n;
        return;
    }
    //TODO: apply to the degree of the tree node, not just left and right
    if (T)
        match(P, T->l);
    if (T)
        match(P, T->r);
}

bool Rule::compare(Node *P, Node *U)
{
    //printf("%s %s\n", U->d, P->d);

    //step 1: check for empty nodes

    if (!U && !P) //if both nodes are empty, the comparison came to end and they are the same
    {
        return true;
    }
    else if (!U) //if only one node is empty, they aren't the same
    {
        return false;
    }
    else if (!P)
    {
        return false;
    }

    //step 2: compare the nodes
    if (!compareNode(P, U)) //instead of "=="
    {
        return false;
    }

    //step 3: compare the chlidren nodes recursively
    //TODO: apply to the degree of the tree node, not just left and right
    if (!compare(P->l, U->l))
    {
        return false;
    }
    if (!compare(P->r, U->r))
    {
        return false;
    }

    return true;
}
