#ifndef EcfSimplificator_h
#define EcfSimplificator_h

#include <string>
#include <memory>
#include <cmath>
#include <ecf/ECF.h>

#include "Node.hpp"
#include "RuleSet.hpp"

class ECFSimplificator
{

private:
	shared_ptr<RuleSet> rules;
public:
	void simplify(Tree::Tree* tree);
    bool reduceConstants(Tree::Tree* tree);
    void loadOperators(StateP state);

    ECFSimplificator(std::string rulesPath);
};

#endif //EcfSimplificator_h