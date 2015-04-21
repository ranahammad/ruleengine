/*
 * RuleConstantContainer.h
 *
 *  Created on: 20/03/2015
 *      Author: jfsvak
 */

#ifndef RULEENGINE_RULECONSTANTCONTAINER_H_
#define RULEENGINE_RULECONSTANTCONTAINER_H_

#include <string>
#include <vector>
#include <map>

#include "sbxTypes.h"
#include "Constant.h"

namespace sbx {

class RuleConstantContainer {

public:
	void initGlobalConstants(const std::vector<sbx::Constant> &globalConstants);
	void initContext(const short underkoncept_oid, const short unionAgreementOid);
	std::vector<std::string> getOptions(const sbx::ProductElementNames productElement);
	std::vector<std::shared_ptr<sbx::Constant>> getOptionsList(const sbx::ProductElementNames productElement);
	std::shared_ptr<sbx::Constant> getConstant(const sbx::ProductElementNames productElement, const sbx::ComparisonTypes comparisonType);
	void printConstantHeader() const;
	void printConstants() const;
private:
	/**
	 * vector of all global constants for all contexts
	 */
	std::vector<Constant> _globalConstants;

	/**
	 *  _ukOptionsMap
	 *  Map of map to a vector of pointers to Constant in _globalConstants
	 *  First index is underKonceptOid
	 *  Second index is ProductElementOid
	 *  Subscript format is: _ukOptionsMap[underkonceptOid][productElementOid]
	 *  Value is a vector of shared_ptr->Constant
	 **/
	std::map<short, std::map<sbx::ProductElementNames, std::vector<std::shared_ptr<sbx::Constant>>>> _ukOptionsMap;

	/**
	 * _ukMinValuesMap:
	 * First index is underKonceptOid
	 * Second index is productElementOid, value is a pointer to the constant-instance in _globalConstants
	 * Subscript format is: _ukMinValuesMap[underkonceptOid][productElementOid]
	 * Value: shared_ptr to Constant
	 */
	std::map<short, std::map<sbx::ProductElementNames, std::shared_ptr<sbx::Constant>>> _ukMinValuesMap;

	/**
	 * _ukMaxValuesMap:
	 * First index is underKonceptOid
	 * Second index is productElementName, value is a pointer to the constant-instance in _globalConstants
	 * Subscript format is: _ukMinValuesMap[underkonceptOid][productElementOid]
	 * Value: shared_ptr to Constant
	 */
	std::map<short, std::map<sbx::ProductElementNames, std::shared_ptr<sbx::Constant>>> _ukMaxValuesMap;
	void printConstant(const std::shared_ptr<sbx::Constant> c) const;
	short _underKonceptOid;
	short _unionAgreementOid;
	bool _contextInitialised;
};

} // sbx namespace end

#endif /* RULEENGINE_RULECONSTANTCONTAINER_H_ */