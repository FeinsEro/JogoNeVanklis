#pragma once
#include "Character.hpp"

class Player : public Character {

public:
	Player(unsigned int x, unsigned int y, const char* name);

	void DoEvents() {}
	void Falar() {}
	void Andar() {}
	void Lutar() {}
	void Reviver() {}

};