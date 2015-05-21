/*
 * sbxFirma.cpp
 *
 *  Created on: 15/12/2014
 *      Author: xjes
 */

#include "KonceptInfo_sbx.h"

namespace sbx {

KonceptInfo::KonceptInfo()
		: _underkonceptOid {0},
		  _numberOfEmployees {0},
		  _numberOfRiskGroupC {0}
{}

KonceptInfo::KonceptInfo(unsigned short underkonceptOid)
		: _underkonceptOid {underkonceptOid},
		  _numberOfEmployees {0},
		  _numberOfRiskGroupC {0}
{}

KonceptInfo::KonceptInfo(unsigned short underkonceptOid, const std::map<unsigned short, std::string>& parameterValues)
		: _underkonceptOid {underkonceptOid},
		  _numberOfEmployees {0},
		  _numberOfRiskGroupC {0},
		  _parameterValues {parameterValues}
{}

void KonceptInfo::addParameterValue(unsigned short parameterOid, std::string value)
{
	_parameterValues.insert( {parameterOid, value} );
}

unsigned short KonceptInfo::getUnderkonceptOid() const
{
	return _underkonceptOid;
}

const std::map<unsigned short, std::string>& KonceptInfo::getParameterValues() const
{
	return _parameterValues;
}

bool KonceptInfo::isParameterSelected(unsigned short parameterOid) const
{
	return (_parameterValues.find(parameterOid) != _parameterValues.cend());
}

void sbx::KonceptInfo::addParameterValue(unsigned short parameterOid, bool selected)
{
	_parameterValues.insert( {parameterOid, (selected) ? "true" : "false"});
}

unsigned short sbx::KonceptInfo::getNumberOfEmployees() const
{
	return _numberOfEmployees;
}

unsigned short sbx::KonceptInfo::getNumberOfRiskGroupC() const
{
	return _numberOfRiskGroupC;
}

KonceptInfo::~KonceptInfo() { }

} /* namespace sbx */
