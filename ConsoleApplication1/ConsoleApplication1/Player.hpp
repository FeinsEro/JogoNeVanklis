#pragma once
#include "Character.hpp"

class Player : public Character {

public:
	Player(unsigned int x, unsigned int y, const char* name);

	void DoEvents() {}
	std::string Falar() { return ""; }
	void Andar() {}
	void Lutar() {}
	void Reviver() {}

};