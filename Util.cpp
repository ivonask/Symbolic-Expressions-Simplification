#include "Util.hpp"
#include <string>
#include <cctype>
#include <math.h>

vector<string> Util::operators;
map<string, OperatorNode *> Util::operatorsInfo;

bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

vector<string> Util::split(const string &str, const string &delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty())
            if (isNumber(token))
            {
                token = "D_" + token;
            }
        tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

bool Util::isOperatorLoaded(string name)
{
    map<string, OperatorNode *>::iterator it = operatorsInfo.find(name);
    return (it != operatorsInfo.end());
}

OperatorNode *Util::getOperatorInfo(string name)
{
    return operatorsInfo.at(name);
}

void Util::loadOperators() //TODO make dependent on the RuleSet?
{
    operatorsInfo.insert(pair<string, OperatorNode *>("+", new OperatorNode("+", 2))); //TODO check defined operators from ECF file.
    operatorsInfo.insert(pair<string, OperatorNode *>("-", new OperatorNode("-", 2)));
    operatorsInfo.insert(pair<string, OperatorNode *>("*", new OperatorNode("*", 2)));
    operatorsInfo.insert(pair<string, OperatorNode *>("/", new OperatorNode("/", 2)));
    operatorsInfo.insert(pair<string, OperatorNode *>("sqr", new OperatorNode("sqr", 1)));
    operatorsInfo.insert(pair<string, OperatorNode *>("pos", new OperatorNode("pos", 1)));

    operatorsInfo.insert(pair<string, OperatorNode *>("sin", new OperatorNode("sin", 1)));
    operatorsInfo.insert(pair<string, OperatorNode *>("cos", new OperatorNode("cos", 1)));

    // operatorsInfo.insert(pair<string, OperatorNode *>("ifpos", new OperatorNode("ifpos", 3)));

    // operatorsInfo.insert(pair<string, OperatorNode *>("or", new OperatorNode("or", 2)));
    // operatorsInfo.insert(pair<string, OperatorNode *>("and", new OperatorNode("and", 2)));
    // operatorsInfo.insert(pair<string, OperatorNode *>("not", new OperatorNode("not", 1)));
    // operatorsInfo.insert(pair<string, OperatorNode *>("xor", new OperatorNode("xor", 2)));
}
Rule *Util::loadRule(string rule)
{
    vector<string> ruleVec = split(rule, "->");
    return new Rule(ruleVec[0], ruleVec[1]);
}

RuleSet *Util::loadRulesFromFile(string file_in)
{
    vector<Rule *> rules;
    ifstream file(file_in);
    if (!file)
    {
        cout << "Unable to open file " << file_in;
        return nullptr;
    }
    string str;
    while (std::getline(file, str))
    {
        rules.push_back(loadRule(str));
    }
    file.close();
    return new RuleSet(rules);
}

ExpressionTree *Util::loadExpressionFromFile(string file_in)
{
    ifstream file(file_in);
    if (!file)
    {
        cout << "Unable to open file " << file_in;
        return nullptr;
    }
    string str;
    getline(file, str);
    file.close();
    return new ExpressionTree(str);
}

void Util::printTree(ExpressionTree *et)
{
    cout << "Prefix : ";
    et->prefix();
    cout << "\nInfix : ";
    et->infix();
    cout << "\n\n";
}

bool Util::reduceConstants(Node *n)
{
    bool reduced = false;
    if (n != NULL)
    {
        bool toReduce = false;
        if (ExpressionTree::isOperator(n->d))
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
                ExpressionTree *et = new ExpressionTree(n);
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

                string res_str = "D_" + to_string(res);

                *n = new Node(res_str);
                reduced = true;
            }
        }

        if (n->chlidren.size() > 0)
        {
            for (int i = 0; i < n->chlidren.size(); i++)
                reduced = reduceConstants(n->chlidren[i]) || reduced;
        }
    }
    return reduced;
}
