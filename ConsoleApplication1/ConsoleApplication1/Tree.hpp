#pragma once

#include "Character.hpp"

class Tree : public Character {

public:
	Tree(unsigned int x, unsigned int y);


	std::string Falar() override { return "Eu sou uma árvore. Eu não falo, idiota."; }
	void Andar(float deltax, float deltay) override {}
	void Lutar() override {}
	void DoEvents(void* charmanager, Map* map) override {}
	void Reviver() override {}

	int GetAngle() { return 0; }

	Character* Clone(float x, float y) override;

};