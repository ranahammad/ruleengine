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
#include <set>
#include <map>
#include <memory>

#include "sbxTypes.h"
#include "Constant_sbx.h"
#include "Product_sbx.h"
#include "Parameter_sbx.h"
#include "ProductElement_sbx.h"
#include "../json/json.h"

namespace sbx {

class RuleConstantContainer {

public:
	static bool _printDebug;

	void initGlobalConstants(const std::vector<sbx::Constant>& globalConstants);
	void initConstants(const std::string& jsonContents);
	void initContext(const unsigned short underkoncept_oid, const short unionAgreementOid);
	std::vector<std::string> getOptions(const sbx::ProductElementOid& productElementOid);
	std::vector<std::string> getOptions(unsigned short productElementOid);
	const std::vector<std::shared_ptr<sbx::Constant>>& getOptionsList(const sbx::ProductElementOid& productElement);
	std::shared_ptr<sbx::Constant> getConstant(const sbx::ProductElementOid& productElement, const sbx::ComparisonTypes& comparisonType);
	std::shared_ptr<sbx::Constant> getConstant(const unsigned short& productElementOid, const sbx::ComparisonTypes& comparisonType);

	const std::set<unsigned short>& getProductOids(unsigned short parameterOid) const;
	std::set<unsigned short> getProductElementOids(unsigned short parameterOid) const;
	sbx::ProductElement getProductElement(const unsigned short& productElementOid);
	sbx::ProductElement getProductElement(const sbx::ProductElementOid& productElementOid);

	std::shared_ptr<sbx::Constant> createConstant(unsigned short underkonceptOid, unsigned short unionAgreementOid, sbx::ProductElementOid peOid, sbx::ComparisonTypes comparisonType);
	// ----- util functions------
	void printConstantHeader() const;
	void printConstants() const;
	void printConstants(unsigned short int underKonceptOid, sbx::ProductElementOid productElement) const;
	void printContainerOverview(unsigned short int underKonceptOid) const;
	void printContainerOverview(unsigned short int underKonceptOid, sbx::ComparisonTypes type) const;
	void printProducts() const;
	void printParameters() const;
	void printParametersToProducts(unsigned short underkonceptOid) const;
	std::size_t size() const;
private:
    
	void printConstant(const std::shared_ptr<sbx::Constant>& c) const;
    void _initInternalMaps();
	void _initRuleConstants(const Json::Value& ruleConstantsList);
	void _initProducts(const Json::Value& products);
	void _initParameters(const Json::Value& parameters);
	void _initParametersToProducts(const Json::Value& parameters);

	/**
	 * vector of shared pointers holding all global constants for all contexts
	 */
	std::vector<std::shared_ptr<Constant>> _globalConstants;

	/**
	 *  _ukOptionsMap
	 *  Map of map to a vector of pointers to Constant in _globalConstants
	 *  First index is underKonceptOid
	 *  Second index is ProductElementOid
	 *  Subscript format is: _ukOptionsMap[underkonceptOid][productElementOid]
	 *  Value is a vector of shared_ptr->Constant
	 **/
	std::map<unsigned short, std::map<sbx::ProductElementOid, std::vector<std::shared_ptr<sbx::Constant>>>> _ukOptionsMap;

	/**
	 * _ukMinValuesMap:
	 * First index is underKonceptOid
	 * Second index is productElementOid, value is a pointer to the constant-instance in _globalConstants
	 * Subscript format is: _ukMinValuesMap[underkonceptOid][productElementOid]
	 * Value: shared_ptr to Constant
	 */
	std::map<unsigned short, std::map<sbx::ProductElementOid, std::shared_ptr<sbx::Constant>>> _ukMinValuesMap;

	/**
	 * _ukMaxValuesMap:
	 * First index is underKonceptOid
	 * Second index is productElementName, value is a pointer to the constant-instance in _globalConstants
	 * Subscript format is: _ukMinValuesMap[underkonceptOid][productElementOid]
	 * Value: shared_ptr to Constant
	 */
	std::map<unsigned short, std::map<sbx::ProductElementOid, std::shared_ptr<sbx::Constant>>> _ukMaxValuesMap;

	/**
	 * _productsMap:
	 * Index is productOid (unsigned short)
	 * Values is a shared_ptr to a Product
	 */
	std::map<unsigned short, std::shared_ptr<sbx::Product>> _productsMap;

	/**
	 * _productElementsMap:
	 * Index is productOid (unsigned short)
	 * Values is a shared_ptr to a ProductElement
	 */
	std::map<unsigned short, std::shared_ptr<sbx::ProductElement>> _productElementMap;
	std::map<unsigned short, sbx::Parameter> _parameterMap;

	/**
	 * First index is underKonceptOid
	 * Second index is parameter
	 * Value is a set of allowed products
	 */
	std::map<unsigned short, std::map<unsigned short, std::set<unsigned short>>> _parameterOidToProductOids;

	/**
	 * First index is underKonceptOid
	 * Second index is parameter
	 * Value is a set of allowed product element oids
	 */
	std::map<unsigned short, std::map<unsigned short, std::set<unsigned short>>> _parameterOidToProductElementOids;

	short _underKonceptOid;
	short _unionAgreementOid;
	bool _contextInitialised;
};

} // sbx namespace end

#endif /* RULEENGINE_RULECONSTANTCONTAINER_H_ */