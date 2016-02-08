#pragma once

/*	Character Manager
	Gerencia os chars do jogo, */
#include <vector>
#include "Character.hpp"
#include "Player.hpp"

class CharacterManager {
private:
	std::vector<Character*> _chars;

public:
	CharacterManager();
	void AddCharacter(Character*);
	void RemoveCharacter(int id);

};