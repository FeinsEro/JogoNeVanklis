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

	inline void GetAllChars(std::vector<Character*>* chars) { *chars = _chars; }

	void AddCharacter(Character*);
	void RemoveCharacter(int id);

	/* Verifica quem está mais próximo de você, numa determinada direção*/
	Character* GetNearestCharacter(Character*, int angle);

	/* Inicia uma luta simples. */
	void DoFight(Character* attacker, Character* defender);

	void DoAllEvents();

};