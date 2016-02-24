#pragma once

/* Classe base para azinimiga */

#include "Character.hpp"

class BaseEnemy : public Character {

public:
	/* Futuramente vou pensar nos métodos dessa classe */
	
	/* Usadas pelo EnemyFactory para criar os inimigos. */
	virtual BaseEnemy* CloneEnemy(unsigned int x, unsigned int y);


	void DoEvents(void* cm, Map* map) override {}
	std::string Falar() override  { return ""; }
	void Andar(int deltax, int deltay) override {}
	void Lutar() override {}
	void Reviver() override {}

};