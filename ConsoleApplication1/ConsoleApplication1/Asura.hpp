#pragma once
#include "Character.hpp"
#include "Animation.hpp"
#include "CharacterManager.hpp"

class Asura : public Character {
private:

	int _angle;
public:
	Asura(unsigned int x, unsigned int y);

	void DoEvents(void* cm, Map* map);

	void Control(Map* map);

	std::string Falar();
	void Andar(float, float);
	void Lutar() {}
	void Reviver() {}

	int GetAngle();
};
