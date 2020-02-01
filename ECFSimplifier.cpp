#include "ECFSimplifier.hpp"


void ECFSimplifier::registerParameters(StateP state)
{
	state->getRegistry()->registerEntry("simplifier.rulespath", (voidP)(new std::string), ECF::STRING);
	state->getRegistry()->registerEntry("simplifier.frequency", (voidP)(new uint(0)), ECF::UINT);
}

bool ECFSimplifier::initialize(StateP state)
{
	state_ = state;
	loadOperators(state);

	if (!state->getRegistry()->isModified("simplifier.rulespath")) {
		this->rules = make_shared<RuleSet>("defaultRules.txt");
	}
	else {
		voidP sptr = state->getRegistry()->getEntry("simplifier.rulespath");
		this->rules = make_shared<RuleSet>(*((std::string*)sptr.get()));
	}

	if (state->getRegistry()->isModified("simplifier.frequency")) {
		voidP sptr = state->getRegistry()->getEntry("simplifier.frequency");
		this->frequency = *((uint*)sptr.get());
	}
	else {
		this->frequency = DEFAULT_FREQ;
	}

	return true;
}

bool ECFSimplifier::operate(StateP state)
{
	return false;
}

ECFSimplifier::ECFSimplifier(std::string rulesPath, StateP state)
{
	state_ = state;
	loadOperators(state);
	this->rules = make_shared<RuleSet>(rulesPath);
	frequency = 1;
}

ECFSimplifier::ECFSimplifier()
{
}

std::string getTreeTrimmed(std::string inputTree)
{
	int pos = inputTree.find(">");
	inputTree = inputTree.substr(pos + 1);

	pos = inputTree.find("<");
	inputTree = inputTree.substr(0, pos);
	return inputTree;
}

std::string getTreeFull(std::string inputTree)
{
	return "<Tree size=\"" + std::to_string(Util::getNoTokens(inputTree)) + "\">" + inputTree + "</Tree>";
}

bool isReducible(shared_ptr<Node> n)
{
	bool toReduce = true;
	if (Simplifier::isOperatorLoaded(n->d))
	{
		for (int i = 0; i < n->chlidren.size(); i++)
		{
			if (Simplifier::isOperatorLoaded(n->chlidren[i]->d))
			{
				toReduce = isReducible(n->chlidren[i]) && toReduce;
			}
			else if (!ExpressionTree::isConstant(n->chlidren[i]->d))
			{
				toReduce = false;
			}
			else
				toReduce = true && toReduce;
		}
		return toReduce;
	}
	else if (ExpressionTree::isConstant(n->d))
	{
		return true && toReduce;
	}
	else
		return false;
}

bool reduce(shared_ptr<Node> n, Tree::Tree *tree)
{
	bool reduced = false;
	if (n != NULL)
	{
		if (isReducible(n) && n->chlidren.size() > 0)
		{
			shared_ptr<ExpressionTree> subTree = make_shared<ExpressionTree>(n);
			cout << "Reducing expression " << subTree->prefix() << endl;

			XMLNode xTree = XMLNode::parseString(getTreeFull(subTree->prefix()).c_str());
			Tree::Tree *newTree = tree->copy();
			newTree->read(xTree);
			double result;
			newTree->execute(&result);

			delete newTree;

			string res_str = to_string(result);

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

			////for scheduling example only!
			//if (res_str == "D_0" || res_str == "D_1") {


			//	shared_ptr<Node> n2 = make_shared<Node>(res_str);
			//	*n = *n2;
			//	reduced = true;
			//}
			//else {
			//	return false;
			//}

			shared_ptr<Node> n2 = make_shared<Node>(res_str);
			*n = *n2;
			reduced = true;
		}

		else if (n->chlidren.size() > 0)
		{
			for (int i = 0; i < n->chlidren.size(); i++)
			{
				reduced = reduce(n->chlidren[i], tree) || reduced;
			}
		}
	}
	return reduced;
}

bool ECFSimplifier::reduceConstants(Tree::Tree *tree)
{
	std::string izraz = getTreeTrimmed(tree->toString());
	shared_ptr<ExpressionTree> wholeTree = make_shared<ExpressionTree>(izraz);
	shared_ptr<Node> n = wholeTree->peek();

	bool reduced = reduce(n, tree);

	wholeTree = make_shared<ExpressionTree>(n);
	std::string wholestr = wholeTree->prefix();
	XMLNode xTree = XMLNode::parseString(getTreeFull(wholestr).c_str());
	tree->read(xTree);
	return reduced;
}
void ECFSimplifier::loadOperators(StateP state)
{
	Tree::Tree *tree = (Tree::Tree *)state->getGenotypes().at(0).get();
	if (tree->getName() != "Tree") {
		cout << "Error: bad genotype. Loading operators for simpification requires tree as the first genotype. Exiting.";
		exit(1);
	}
	// listing all used functions and adding them to a map
	std::map<std::string, Tree::PrimitiveP>::iterator it = tree->primitiveSet_->mAllPrimitives_.begin();
	std::map<std::string, int> operatorsMap;
	while (it != tree->primitiveSet_->mAllPrimitives_.end())
	{
		Tree::PrimitiveP func;
		if (func = tree->primitiveSet_->getFunctionByName(it->first))
		{
			operatorsMap.insert(pair<string, int>(func->getName(), func->getNumberOfArguments()));
		}
		it++;
	}

	Simplifier::loadOperators(operatorsMap);
}

void ECFSimplifier::simplify(Tree::Tree *tree)
{
	if (frequency <= 0) return;


	else if (state_->getGenerationNo() % frequency != 0) return;

	std::string treeStr = getTreeTrimmed(tree->toString());
	std::shared_ptr<ExpressionTree> expression = make_shared<ExpressionTree>(treeStr);

	cout << "\nInitial expression: ";
	cout << expression->prefix().c_str();
	cout << "\n\n";


	reduceConstants(tree);

	treeStr = getTreeTrimmed(tree->toString());
	expression = make_shared<ExpressionTree>(treeStr);


	//if (counter.empty())
	//{
	//	for (int i = 0; i < rules->size(); i++)
	//	{
	//		counter.push_back(0);
	//	}
	//}

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
				reduce(expression->peek(), tree);

				cout << "New expression: ";
				cout << expression->prefix().c_str();
				cout << "\n\n";

				//counter[i]++;

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

	XMLNode xTree = XMLNode::parseString(getTreeFull(expression->prefix()).c_str());
	tree->read(xTree);
}