//============================================================================
// Name        : helloworld2.cpp
// Author      : xjes
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef RULEENGINE_RULEENGINE_H_
#define RULEENGINE_RULEENGINE_H_

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "muParser/mpParser.h"
#include "sbxTypes.h"
#include "RuleConstantContainer.h"
#include "Constant.h"
#include "ProductElementValue.h"

namespace sbx {

class RuleEngine {
  public:
	static const int VALID = 1;
	static const int INVALID = -1;
	void initConstants(const std::vector<Constant> &globalConstants);
	void initContext(const short underkoncept_oid, const short unionagreement_oid);
	std::vector<std::string> getOptions(const sbx::ProductElementNames productElement);
	std::vector<std::shared_ptr<Constant>> getOptionsList(const sbx::ProductElementNames productElement);
	std::shared_ptr<sbx::Constant> getConstant(const sbx::ProductElementNames productElement, const sbx::ComparisonTypes comparisonType);
	int validate(const sbx::ProductElementNames productElement, const std::vector<std::pair<std::string,long>>);
	int validate(const sbx::ProductElementValue &peValue);
	const int validate(const sbx::ComparisonTypes comparisonType) const;
  private:
	sbx::RuleConstantContainer _container;
	std::map<sbx::ProductElementNames, std::vector<std::string>> _ruleCatalogue;
    // mup::ParserX p;

	// private util methods
	void printVariables(mup::ParserX p);
	void printExpressions(mup::ParserX p);
	void loadRuleConstants(mup::ParserX&);
	void loadRuleCatalogue();
};

} // sbx namespace end

#endif // RULEENGINE_RULEENGINE_H_