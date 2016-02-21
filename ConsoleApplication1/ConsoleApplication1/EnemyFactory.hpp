#pragma once

/* Cria inimigos automaticamente*/
#include <map>

#include "BaseEnemy.hpp"
#include "CharacterManager.hpp"

class EnemyFactory {
private:
	std::map<int /*typeid*/, BaseEnemy*> _enemies_list; //Lista dos inimigos
	CharacterManager* _cm;

public:
	EnemyFactory(CharacterManager* cm);

	void RegisterEnemy(int type_id, BaseEnemy* enemy_instance);
	void PutEnemy(int type_id, unsigned int x, unsigned int y);

	~EnemyFactory();
};

