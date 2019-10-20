#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>

#include "ExpressionTree.hpp"

using namespace std;

vector<string> split(const string &str, const string &delim)
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

int main()
{
    string s = "+ + X * Y Z Y";
    ExpressionTree et;
    string delimeter = " ";
    vector<string> splitted = split(s, delimeter);
    int m = splitted.size();
    et.buildTree(splitted);
    cout << "Prefix : ";
    et.prefix();
    cout << "\nInfix : ";
    et.infix();
}