/*
 * RuleCatalogue.cpp
 *
 *  Created on: 16/05/2015
 *      Author: jespe_000
 */

#include "RuleCatalogue.h"

#include <vector>
#include <memory>


namespace sbx {

RuleCatalogue::RuleCatalogue()
		: _parent { nullptr }
{}

RuleCatalogue::RuleCatalogue(std::shared_ptr<sbx::Rule> parent)
		: _parent { parent }
{
}

std::vector<std::shared_ptr<sbx::Rule>> RuleCatalogue::getRules()
{
	return _rules;
}

void RuleCatalogue::addRule(std::shared_ptr<sbx::Rule> rule)
{
	_rules.push_back(rule);
}

std::shared_ptr<sbx::Rule> RuleCatalogue::getParent()
{
	return _parent;
}

void RuleCatalogue::setParent(std::shared_ptr<sbx::Rule> parent)
{
	_parent = parent;
}

RuleCatalogue::~RuleCatalogue()
{
}

} /* namespace sbx */
