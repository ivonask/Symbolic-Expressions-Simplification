#include "Simplifier.hpp"
#include "Util.hpp"

#include <string>
#include <math.h>

vector<string> Simplifier::operators;
map<string, shared_ptr<OperatorNode>> Simplifier::operatorsInfo;

Simplifier::Simplifier(string rulesPath, string operatorsPath)
{
    loadOperators(operatorsPath);
    this->rules = make_shared<RuleSet>(rulesPath);
}

Simplifier::Simplifier()
{
}

void Simplifier::setRules(shared_ptr<RuleSet> rules)
{
    this->rules = rules;
}

shared_ptr<RuleSet> Simplifier::getRules()
{
    return rules;
}

int Simplifier::simplify(shared_ptr<ExpressionTree> expression)
{
    if (counter.empty())
    {
        for (int i = 0; i < rules->size(); i++)
        {
            counter.push_back(0);
        }
    }

    cout << "\nInitial expression: ";
    cout << expression->prefix().c_str();
    cout << "\n\n";

    int appliedRules = 0;

    bool reset = true;
    vector<shared_ptr<Rule>>::iterator itr;
    int cnt = 0;
    int MAX_ITERATIONS = 100; //security reasons: in case rules are written in a way which can make an infinite loop
    do
    {
        reset = false;

        int i = 0;
        for (i = 0; i < rules->size(); i++)
        {
            if (rules->getRule(i)->applyRule(expression))
            {
                reduceConstants(expression->peek());

                cout << "New expression: ";
                cout << expression->prefix().c_str();
                cout << "\n\n";

                appliedRules++;
                counter[i]++;

                reset = true;
                break;
            }
        }
        if (cnt >= MAX_ITERATIONS)
        {
            cnt = 0;
            reset = true;
        }
        cnt++;
    } while (reset);

    cout << "Final result: ";
    cout << expression->prefix().c_str();
    cout << "\n";

    return appliedRules;
}

bool Simplifier::isOperatorLoaded(string name)
{
    map<string, shared_ptr<OperatorNode>>::iterator it = operatorsInfo.find(name);
    return (it != operatorsInfo.end());
}

shared_ptr<OperatorNode> Simplifier::getOperatorInfo(string name)
{
    return operatorsInfo.at(name);
}

void Simplifier::loadOperators(string file_in)
{
    ifstream file(file_in);
    if (!file)
    {
        cout << "Unable to open file " << file_in;
        return;
    }
    string str;
    while (std::getline(file, str))
    {
        vector<string> vec = Util::split(str, " ", false);
        operatorsInfo.insert(pair<string, OperatorNode *>(vec[0], new OperatorNode(vec[0], stoi(vec[1]))));
    }
    file.close();
}

void Simplifier::loadOperators(map<string, int> ops)
{
    map<string, int>::iterator itr;
    for (itr = ops.begin(); itr != ops.end(); ++itr)
    {
        operatorsInfo.insert(pair<string, OperatorNode *>(itr->first, new OperatorNode(itr->first, itr->second)));
    }
}

bool isReducable(string s)
{
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "sin" || s == "cos");
}

bool Simplifier::reduceConstants(shared_ptr<Node> n)
{
    bool reduced = false;
    bool reducedNow;
    do
    {
        reducedNow = false;
        if (n != NULL)
        {
            bool toReduce = false;
            if (isReducable(n->d))
            {
                for (int i = 0; i < n->chlidren.size(); i++)
                {
                    if (!ExpressionTree::isConstant(n->chlidren[i]->d))
                    {
                        toReduce = false;
                        break;
                    }
                    toReduce = true;
                }

                if (toReduce)
                {
                    shared_ptr<ExpressionTree> et = make_shared<ExpressionTree>(n);
                    cout << "Reducing expression " << et->prefix() << endl;

                    double res, first, second;
                    first = atof(n->chlidren[0]->d.substr(2).c_str());

                    if (operatorsInfo.at(n->d)->numberOfChildren() == 2)
                    {
                        second = atof(n->chlidren[1]->d.substr(2).c_str());

                        if (n->d == "+")
                            res = first + second;

                        else if (n->d == "-")
                            res = first - second;

                        else if (n->d == "*")
                            res = first * second;

                        else if (n->d == "/")
                            res = first / second;
                    }
                    else if (operatorsInfo.at(n->d)->numberOfChildren() == 1)
                    {
                        if (n->d == "sin")
                            res = sin(first);
                        else if (n->d == "cos")
                            res = cos(first);
                    }

                    string res_str = to_string(res);

                    //check for neg 0:
                    if (res_str == "-0.000000")
                        res_str = "0";

                    //remove extra trailing zeros:
                    while (res_str.find_last_of("0") == res_str.length() - 1 || res_str.find_last_of(".") == res_str.length() - 1)
                    {
                        if (res_str == "0")
                        {
                            break;
                        }
                        res_str = res_str.substr(0, res_str.length() - 1);
                    }

                    res_str = "D_" + res_str;

                    shared_ptr<Node> n2 = make_shared<Node>(res_str);
                    *n = *n2;
                    reducedNow = true;
                }
            }

            if (n->chlidren.size() > 0)
            {
                for (int i = 0; i < n->chlidren.size(); i++)
                    reducedNow = reduceConstants(n->chlidren[i]) || reducedNow;
            }
        }
        reduced = reducedNow || reduced;
    } while (reducedNow == true);
    return reduced;
}

vector<int> Simplifier::getCounter()
{
    return counter;
}