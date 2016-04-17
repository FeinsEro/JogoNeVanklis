#pragma once

/* Cria inimigos automaticamente*/
#include <map>

#include "Character.hpp"
#include "CharacterManager.hpp"

class CharFactory {
private:
	std::map<int /*typeid*/, Character*> _enemies_list; //Lista dos inimigos
	CharacterManager* _cm;

public:
	CharFactory(CharacterManager* cm);

	void RegisterCharacter(int type_id, Character* char_instance);
	Character* PutCharacter(int type_id, unsigned int x, unsigned int y);
	Character* PutCharacter(int type_id, int id, unsigned int x, unsigned int y, int hp);

	~CharFactory();
};

