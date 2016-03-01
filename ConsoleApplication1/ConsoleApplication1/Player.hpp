#pragma once
#include "Character.hpp"

class Player : public Character {

public:
	Player(unsigned int x, unsigned int y, const char* name);

	void DoEvents(void* cm, Map* map);
	std::string Falar() { return ""; }
	void Andar(float deltax, float deltay);
	void Lutar() {}
	void Reviver() {}

};