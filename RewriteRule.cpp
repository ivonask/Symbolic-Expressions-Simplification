#include "RewriteRule.hpp"

Rule::Rule(string original, string replacement)
{
    this->original = original;
    this->replacement = replacement;
}

ExpressionTree Rule::applyRule(ExpressionTree expression, Rule rule)
{
    ExpressionTree result;
    return result;
}
