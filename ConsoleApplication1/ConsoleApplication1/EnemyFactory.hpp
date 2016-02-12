#pragma once

/* Cria inimigos automaticamente*/
#include <map>

#include "BaseEnemy.hpp"

class EnemyFactory {
private:
	std::map<int, BaseEnemy> _enemies_list; //Lista dos inimigos

};