#pragma once

/*	Character Manager
	Gerencia os chars do jogo, */
#include <vector>
#include <cmath>

#include "Character.hpp"
#include "Player.hpp"
#include "Map.hpp"

enum TypeIDList {
	TYPEID_PLAYER = 0,
	TYPEID_TREE1 = 1,
	TYPEID_ASURA = 66,
	TYPEID_AKHBRAN = 67,
};

class CharacterManager {
private:
	std::vector<Character*> _chars;
	Map* _map = NULL;
public:
	CharacterManager();

	inline void GetAllChars(std::vector<Character*>* chars) { *chars = _chars; }

	inline void SetMap(Map* map) { _map = map; }
	inline Map* GetMap() { return _map; }

	Player* _player;


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

	void SetPlayer(Player*);
	Player* GetPlayer();

};