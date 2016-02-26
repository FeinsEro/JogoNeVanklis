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

	/* Verifica quem est� mais pr�ximo de voc�, numa determinada dire��o*/
	Character* GetNearestCharacter(Character*, int angle);

	/*	Verifica quem est� mais pr�ximo de voc�, numa determinada dire��o, 
		numa determinada dist�ncia (em blocos do jogo)*/
	Character* GetNearestCharacterInRange(Character*, float angle, int range);

	/* Inicia uma luta simples. */
	void DoFight(Character* attacker, Character* defender);

	void DoAllEvents();

};