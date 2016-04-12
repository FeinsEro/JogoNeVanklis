#pragma once
#include "Character.hpp"
#include "Animation.hpp"

class Player : public Character {
private:
	
	bool cima = false, baixo = false, direita = false, esquerda = false;
public:
	Player(unsigned int x, unsigned int y, const char* name);

	void DoEvents(void* cm, Map* map);

	void Control(Map* map);

	std::string Falar() { return ""; }
	void Andar(float, float);
	void Lutar() {}
	
	void Reviver() {}

	int GetAngle();

	void SetEventQueue(void* ev);

	void SetSprite(Sprite*);
};