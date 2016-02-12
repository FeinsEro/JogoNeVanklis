#pragma once

/* Classe base para azinimiga */

#include "Character.hpp"

class BaseEnemy : public Character {

public:
	/* Futuramente vou pensar nos métodos dessa classe */
	
	/* Usada pelo EnemyFactory*/
	BaseEnemy(BaseEnemy& b, unsigned int x, unsigned int y);

	void DoEvents() {}
	std::string Falar() { return ""; }
	void Andar() {}
	void Lutar() {}
	void Reviver() {}

};