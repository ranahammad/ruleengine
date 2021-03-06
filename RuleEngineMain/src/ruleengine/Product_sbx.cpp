/*
 * Product.cpp
 *
 *  Created on: 06/05/2015
 *      Author: jfsvak
 */

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>

#include "Product_sbx.h"
using namespace std;

namespace sbx {
bool Product::_printDebug = false;

Product::Product(unsigned short oid, const std::string& name)
		: _oid {oid},
		  _name {name},
		  _productElementOids {}
{
	if (Product::_printDebug) {
		cout << "+ ";
		printValues();
	}
}

Product::Product(const sbx::Product& otherProduct)
		: _oid {otherProduct._oid},
		  _name {otherProduct._name},
		  _productElementOids {otherProduct._productElementOids}
{
	if (Product::_printDebug) {
		cout << "= Ori.Product{"<< addressof(otherProduct) << "}=>";
		printValues();
	}
}

const std::string& Product::getName() const {
	return _name;
}

unsigned short Product::getOid() {
	return _oid;
}

const std::vector<unsigned short>& Product::getProductElementOids() const {
	return _productElementOids;
}

void Product::addProductElementOid(unsigned short oid) {
	_productElementOids.push_back(oid);
}

Product::~Product() {
	if (Product::_printDebug) {
		cout << "- ";
		printValues();
	}
}

void Product::printValues() const
{
	ostringstream s;

	if (_productElementOids.size() > 0) {
		ostream_iterator<unsigned short> oit(s, ", ");
		copy(_productElementOids.cbegin(), _productElementOids.cend(), oit);
	}

	cout << "Product{" << this << ", oid[" << _oid << "], name[" << _name << "], pe[" << s.str() << "]" << endl;
}

}

