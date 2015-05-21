/*
 * ValidationResult.cpp
 *
 *  Created on: 19/05/2015
 *      Author: jfsvak
 */
#include "ValidationResult.h"

#include <iostream>

namespace sbx {

std::ostream& operator << (std::ostream& output, const ValidationResult& valResult) {
	output << "Code[" << (int) valResult.getValidationCode() << "], PE[" << valResult.getVariableName() << " (" << valResult.getProductElementOid() << ")], RuleId[" << valResult.getRuleId() << "], Msg[" << valResult.getMessage() << "]";
	return output;
}

ValidationResult::ValidationResult()
		: _code { sbx::ValidationCode::kUnknown },
		  _productElementOid {0},
		  _ruleId {""},
		  _message {""}
{}

ValidationResult::ValidationResult(unsigned short peOid)
		: _code { sbx::ValidationCode::kUnknown },
		  _productElementOid {peOid},
		  _ruleId {""},
		  _message {""}
{}

/*ValidationResult::ValidationResult(const sbx::ValidationResult& other)
		: _code { other._code },
		  _productElementOid { other._productElementOid },
		  _variableName {other._variableName},
		  _ruleId {other._ruleId},
		  _message { other._message }
{}
*/
ValidationResult::ValidationResult(sbx::ValidationCode code, unsigned short peOid, const std::string& variableName, const std::string& ruleId, const std::string& message)
		: _code { code },
		  _productElementOid {peOid},
		  _variableName {variableName},
		  _ruleId {ruleId},
		  _message {message}
{}


sbx::ValidationCode ValidationResult::getValidationCode() const
{
	return _code;
}

unsigned short ValidationResult::getProductElementOid() const
{
	return _productElementOid;
}

const std::string& ValidationResult::getRuleId() const
{
	return _ruleId;
}

const std::string& ValidationResult::getMessage() const
{
	return _message;
}

ValidationResult& ValidationResult::setValidationCode(sbx::ValidationCode validationCode)
{
	_code = validationCode;
	return *this;
}

ValidationResult& ValidationResult::setProductElementOid(unsigned short productElementOid)
{
	_productElementOid = productElementOid;
	return *this;
}

ValidationResult& ValidationResult::setRuleId(const std::string& ruleId)
{
	_ruleId = ruleId;
	return *this;
}

ValidationResult& ValidationResult::setMessage(const std::string& message)
{
	_message = message;
	return *this;
}

ValidationResult::~ValidationResult()
{}

const std::string& ValidationResult::getVariableName() const
{
	return _variableName;
}

void ValidationResult::setVariableName(const std::string& variableName)
{
	_variableName = variableName;
}

} /* namespace sbx */