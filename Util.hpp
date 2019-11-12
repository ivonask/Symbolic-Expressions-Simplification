#ifndef UTIL_h
#define UTIL_h

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

#include "Operator.hpp"

using namespace std;

class Util
{
private:
    static vector<string> operators;
    static map<string, Operator *> operatorsInfo;

public:
    static vector<string> split(const string &str, const string &delim);
    static bool isOperatorLoaded(string name);
    static Operator *getOperatorInfo(string name);
    static void loadOperators();
};

#endif // UTIL_h