#pragma once
#include "Character.hpp"

class Player : public Character {

public:
	Player(unsigned int x, unsigned int y, const char* name) : Character(NULL, x, y, std::string(name),
		100, 0, 0, 0, 0, 0, 0) {}

	void Falar() {}
	void Andar() {}
	void Lutar() {}
	void Reviver() {}

};