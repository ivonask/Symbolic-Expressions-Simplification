#ifndef EcfSimplificator_h
#define EcfSimplificator_h

#include <string>
#include <memory>
#include <cmath>
#include <ecf/ECF.h>

#include "Node.hpp"
#include "RuleSet.hpp"


class ECFSimplificator : public Operator
{

private:
	shared_ptr<RuleSet> rules;
	uint frequency;

	const uint DEFAULT_FREQ = 0;
	StateP state_;

public:
	ECFSimplificator(std::string rulesPath, StateP state);
	ECFSimplificator();

	void simplify(Tree::Tree* tree);
    bool reduceConstants(Tree::Tree* tree);
    void loadOperators(StateP state);

	void registerParameters(StateP state);
	bool initialize(StateP state);
	bool operate(StateP state);
};

#endif //EcfSimplificator_h