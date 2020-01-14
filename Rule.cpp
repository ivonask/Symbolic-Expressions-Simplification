#include "Rule.hpp"
#include <iostream>
#include <string>

std::map<string, shared_ptr<Node>> variables;

Rule::Rule(string original, string replacement)
{
    this->originalStr = original;
    this->replacementStr = replacement;

    this->original = make_shared<ExpressionTree>(original);
    this->replacement = make_shared<ExpressionTree>(replacement);
}

bool isEqual(shared_ptr<Node> n1, shared_ptr<Node> n2)
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

bool Rule::isAddedToMap(string var, shared_ptr<Node> n)
{
    std::map<string, shared_ptr<Node>>::iterator it = variables.find(var);
    if (it == variables.end())
    {
        variables.insert(pair<string, shared_ptr<Node>>(var, n));
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

void printMap(std::map<string, shared_ptr<Node>> mapVars)
{
    std::map<string, shared_ptr<Node>>::iterator itr;
    cout << "\nThe variables dictionary is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = mapVars.begin(); itr != mapVars.end(); ++itr)
    {
        shared_ptr<ExpressionTree> etp = make_shared<ExpressionTree>(itr->second);
        cout << '\t' << itr->first
             << '\t' << etp->prefix() << '\n';
    }
    cout << endl;
}

bool Rule::compareNode(shared_ptr<Node> n1, shared_ptr<Node> n2)
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
		else {
			return false;
		}
    }
    //case 5: pattern node is a variable, expression a variable or a constant
    else
    {
        return isAddedToMap(n1->d, n2);
    }
}

bool Rule::applyRule(shared_ptr<ExpressionTree> expression)
{
    variables.clear();
    return (match(original->peek(), expression->peek()));
}

bool Rule::match(shared_ptr<Node> P, shared_ptr<Node> T)
{
    if (compare(P, T))
    {
        cout << "Rule applied: " << originalStr << " -> " << replacementStr << "\n";

        replacement = make_shared<ExpressionTree>(replacementStr);

        //printMap(variables);

        //replace the original tree with replacement tree
        shared_ptr<ExpressionTree> translated = replacement->translate(variables);
        *T = *translated->peek();

        return true;
    }

    bool matched = false;
    if (T)
        for (int i = 0; i < T->chlidren.size(); i++)
        {
            matched = match(P, T->chlidren[i]) || matched;
        }
    return matched;
}

bool Rule::compare(shared_ptr<Node> P, shared_ptr<Node> U)
{
    //step 1: check for empty nodes
    if (!U || !P) //if any of the nodes are empty, the comparison came to end and they are the same
    {

        return true;
    }

    //step 2: compare the nodes
    if (!compareNode(P, U)) //true if expression node is successfully mapped to a pattern variable or the nodes are the same
    {
        return false;
    }

    //step 3: compare the chlidren nodes recursively
    for (int i = 0; i < P->chlidren.size(); i++)
        if (!compare(P->chlidren[i], U->chlidren[i]))
        {
            variables.clear(); //important: clear the mappings for this subtree since the matching was unsuccessful
            return false;
        }
    return true;
}

string Rule::printRule()
{
    return originalStr + " -> " + replacementStr;
}
