#include "Rule.hpp"

std::map<string, Node *> variables;

Rule::Rule(string original, string replacement)
{
    this->original = new ExpressionTree(original);
    this->replacement = new ExpressionTree(replacement);
}

bool isEqual(Node *n1, Node *n2)
{
    if (!n1 && !n2) //if both nodes are empty, the comparison came to end and they are the same
    {
        return true;
    }
    if (n1 && n2)
    {
        if (n1->chlidren.size() != n2->chlidren.size())
        {
            return false;
        }
        for (int i = 0; i < n1->chlidren.size(); i++)
        {
            if (!isEqual(n1->chlidren[i], n2->chlidren[i]))
            {
                return false;
            }
        }
        if (n1->d == n2->d)
        {
            return true;
        }
    }
    return false;
}

bool Rule::isAddedToMap(string var, Node *n)
{
    std::map<string, Node *>::iterator it = variables.find(var);
    if (it == variables.end())
    {
        variables.insert(pair<string, Node *>(var, n));
        return true;
    }
    else if (isEqual(variables.find(var)->second, n))
    {
        return true;
    }
    else
    {
        return false;
    }
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
    //case 2: pattern node is a variable, expression node is an operator -> expression subtree is represented as that pattern variable, if constant return false
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
    else if (ExpressionTree::isConstant(n1->d))
    {
        if (ExpressionTree::isConstant(n2->d))
        {
            if (n1->d == n2->d)
                return true; //TODO: is mapping needed?
            else
                return false;
        }
    }
    //case 5: pattern node is a variable, expression a variable or a constant
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

void Rule::match(Node *P, Node *T)
{
    if (compare(P, T))
    {
        cout << "Found a pattern!\n";

        //replace the original tree with replacement tree
        //*T = *replacement->peek();

        ExpressionTree *translated = replacement->translate(variables);

        *T = *translated->peek();
        return;
    }

    if (T)
        for (int i = 0; i < T->chlidren.size(); i++)
            match(P, T->chlidren[i]);
}

bool Rule::compare(Node *P, Node *U)
{
    //printf("%s %s\n", U->d, P->d);

    //step 1: check for empty nodes

    if (!U && !P) //if both nodes are empty, the comparison came to end and they are the same
    {
        return true;
    }
    else if (!U) //TODO: check if there is cases when a subtree is not empty but the compare method should return false. Also think about the general case with more than 2 children.
    {
        return true;
    }
    else if (!P)
    {
        return true;
    }

    //step 2: compare the nodes
    if (!compareNode(P, U)) //instead of "=="
    {
        return false;
    }

    //step 3: compare the chlidren nodes recursively
    //TODO: apply to the degree of the tree node, not just left and right

    for (int i = 0; i < P->chlidren.size(); i++)
        if (!compare(P->chlidren[i], U->chlidren[i]))
        {
            variables.clear();
            return false;
        }

    return true;
}
