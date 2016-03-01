#pragma once

#include "Character.hpp"

class Tree : public Character {

public:
	Tree(unsigned int x, unsigned int y) : Character(NULL, 0, x, y, "�rvore", 0xffffffff) {
		_TypeID = 1;
	}


	std::string Falar() override { return "Eu sou uma �rvore. Eu n�o falo, idiota."; }
	void Andar(float deltax, float deltay) override {}
	void Lutar() override {}
	void DoEvents(void* charmanager, Map* map) override {}
	void Reviver() override {}


	Character* Clone(float x, float y) override;

};