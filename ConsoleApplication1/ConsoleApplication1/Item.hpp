#pragma once

#include <string>

/* Classe genérica para itens */

class Item {
private:
	unsigned int _id;		//id
	unsigned int _value;	//valor em dinheiro
	std::string _name;

public:
	inline unsigned int GetID() { return _id; }

	inline unsigned int GetValue() { return _value; }

	inline void GetName(std::string& name) { name = _name; }


	Item(std::string name, unsigned int value);

};