#include "Util.hpp"
#include <string>
#include <cctype>
#include <math.h>

bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

vector<string> Util::split(const string &str, const string &delim, bool transformConstants)
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
            if (isNumber(token) && transformConstants)
            {
                token = "D_" + token;
            }
        tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

void Util::printTree(shared_ptr<ExpressionTree> et)
{
    cout << "Prefix : ";
    et->prefix();
    cout << "\nInfix : ";
    et->infix();
    cout << "\n\n";
}

int Util::getNoTokens(string expression)
{
    return split(expression, " ", true).size();
}
