#include "Util.hpp"

vector<string> Util::operators;
map<string, Operator *> Util::operatorsInfo;

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
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

bool Util::isOperatorLoaded(string name)
{
    map<string, Operator *>::iterator it = operatorsInfo.find(name);
    return (it != operatorsInfo.end());
}

Operator *Util::getOperatorInfo(string name)
{
    return operatorsInfo.at(name);
}

void Util::loadOperators() //TODO make dependent on the RuleSet?
{
    operatorsInfo.insert(pair<string, Operator *>("+", new Operator("+", 2))); //TODO check defined operators from ECF file.
    operatorsInfo.insert(pair<string, Operator *>("-", new Operator("-", 2)));
    operatorsInfo.insert(pair<string, Operator *>("*", new Operator("*", 2)));
    operatorsInfo.insert(pair<string, Operator *>("/", new Operator("/", 2)));

    operatorsInfo.insert(pair<string, Operator *>("sin", new Operator("sin", 1)));
    operatorsInfo.insert(pair<string, Operator *>("cos", new Operator("cos", 1)));

    operatorsInfo.insert(pair<string, Operator *>("ifpos", new Operator("ifpos", 3)));

    operatorsInfo.insert(pair<string, Operator *>("or", new Operator("or", 2)));
    operatorsInfo.insert(pair<string, Operator *>("and", new Operator("and", 2)));
    operatorsInfo.insert(pair<string, Operator *>("not", new Operator("not", 1)));
    operatorsInfo.insert(pair<string, Operator *>("xor", new Operator("xor", 2)));
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