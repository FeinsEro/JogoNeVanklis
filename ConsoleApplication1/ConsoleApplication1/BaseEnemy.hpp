#pragma once

/* Classe base para azinimiga */

#include "Character.hpp"

class BaseEnemy : public Character {

public:
	/* Futuramente vou pensar nos m�todos dessa classe */
	


	void DoEvents(void* cm, Map* map) override {}
	std::string Falar() override  { return ""; }
	void Andar(float deltax, float deltay) override {}
	void Lutar() override {}
	void Reviver() override {}

};