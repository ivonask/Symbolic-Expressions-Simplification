#ifndef EcfSimplificator_h
#define EcfSimplificator_h

#include <string>
#include <memory>
#include <cmath>
#include <ecf/ECF.h>

#include "Node.hpp"
#include "RuleSet.hpp"
#include "Simplifier.hpp"
#include "Util.hpp"

class ECFSimplifier : public Operator
{

private:
	uint frequency;

	const uint DEFAULT_FREQ = 0;
	StateP state_;

	shared_ptr<RuleSet> rules;

public:
	ECFSimplifier();
	ECFSimplifier(std::string rulesPath, StateP state);

	void simplify(Tree::Tree *tree);
	bool reduceConstants(Tree::Tree *tree);
	void loadOperators(StateP state);

	void registerParameters(StateP state);
	bool initialize(StateP state);
	bool operate(StateP state);
};

#endif //EcfSimplificator_h