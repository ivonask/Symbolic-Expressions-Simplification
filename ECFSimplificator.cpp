#include "ECFSimplificator.hpp"
#include "Util.hpp"

ECFSimplificator::ECFSimplificator(std::string rulesPath)
{
	this->rules = Util::loadRulesFromFile(rulesPath);
}

std::string getTreeTrimmed(std::string inputTree) {
	int pos = inputTree.find(">");
	inputTree = inputTree.substr(pos + 1);

	pos = inputTree.find("<");
	inputTree = inputTree.substr(0, pos);
	return inputTree;
}

std::string getTreeFull(std::string inputTree) {
	return "<Tree size=\"" + std::to_string(Util::getNoTokens(inputTree)) + "\">" + inputTree + "</Tree>";
}

bool isReducible(shared_ptr<Node> n) {
	bool toReduce = true;
	if (Util::isOperatorLoaded(n->d))
	{
		for (int i = 0; i < n->chlidren.size(); i++)
		{
			if (Util::isOperatorLoaded(n->chlidren[i]->d)) {
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
	else if (ExpressionTree::isConstant(n->d)) {
		return true && toReduce;
	}
	else return false;
}

bool reduce(shared_ptr<Node> n, Tree::Tree* tree) {
	bool reduced = false;
	if (n != NULL)
	{
		if (isReducible(n) && n->chlidren.size() > 0)
		{
			shared_ptr<ExpressionTree> subTree = make_shared<ExpressionTree>(n);
			cout << "Reducing expression " << subTree->prefix() << endl;

			XMLNode xTree = XMLNode::parseString(getTreeFull(subTree->prefix()).c_str());
			Tree::Tree* newTree = tree->copy();
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

			shared_ptr<Node> n2 = make_shared<Node>(res_str);
			*n = *n2;
			reduced = true;
		}

		else if (n->chlidren.size() > 0)
		{
			for (int i = 0; i < n->chlidren.size(); i++) {
				reduced = reduce(n->chlidren[i], tree) || reduced;
			}
		}
	}
	return reduced;
}


bool ECFSimplificator::reduceConstants(Tree::Tree* tree)
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
void ECFSimplificator::loadOperators(StateP state) {
	Tree::Tree* tree = (Tree::Tree*) state->getGenotypes().at(0).get();

	// izlistaj sve koristene funkcije
	std::map<std::string, Tree::PrimitiveP>::iterator it = tree->primitiveSet_->mAllPrimitives_.begin();
	std::map<std::string, int> operatorsMap;
	while (it != tree->primitiveSet_->mAllPrimitives_.end()) {
		Tree::PrimitiveP func;
		if (func = tree->primitiveSet_->getFunctionByName(it->first)) {
			cout << func->getName();
			cout << "\t" << func->getNumberOfArguments() << endl;

			operatorsMap.insert(pair<string, int>(func->getName(), func->getNumberOfArguments()));
		}
		it++;
	}

	Util::loadOperators(operatorsMap);
}

void ECFSimplificator::simplify(Tree::Tree* tree) {

	reduceConstants(tree);

	std::string treeStr = getTreeTrimmed(tree->toString());
	std::shared_ptr<ExpressionTree> et = make_shared <ExpressionTree>(treeStr);

	this->rules->applyAllRules(et);

	XMLNode xTree = XMLNode::parseString(getTreeFull(et->prefix()).c_str());
	tree->read(xTree);
}