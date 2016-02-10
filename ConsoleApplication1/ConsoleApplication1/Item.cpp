#pragma once

#include "Item.hpp"

static unsigned int _lastid = 0;

Item::Item(std::string name, unsigned int value) {
	this->_id = _lastid++;
	this->_name = name;
	this->_value = value;


	fprintf(stderr, "[Item] Item \"%s\" criado, id %d\n", name.c_str(), _id);
	fprintf(stderr, "[Item] \t valor: %d\n", _value);
}