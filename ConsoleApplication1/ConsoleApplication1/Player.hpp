#pragma once
#include "Character.hpp"

class Player : public Character {
private:
	
	bool cima = false, baixo = false, direita = false, esquerda = false;
public:
	Player(unsigned int x, unsigned int y, const char* name);

	void DoEvents(void* cm, Map* map);

	void Control(Map* map);

	std::string Falar() { return ""; }
	void Andar(float deltax, float deltay);
	void Lutar() {}
	void Reviver() {}

	void SetEventQueue(void* ev);
};