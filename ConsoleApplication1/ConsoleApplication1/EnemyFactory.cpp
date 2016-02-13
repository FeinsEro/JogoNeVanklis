#include "EnemyFactory.hpp"

EnemyFactory::EnemyFactory(CharacterManager* cm) {
	this->_cm = cm;
}


void EnemyFactory::RegisterEnemy(int type_id, BaseEnemy* enemy_instance) {
	this->_enemies_list[type_id] = enemy_instance;
}
void EnemyFactory::PutEnemy(int type_id, unsigned int x, unsigned int y) {
	
	BaseEnemy* bm = new BaseEnemy(*this->_enemies_list[type_id], x, y);

	bm->SetPosition(x, y);	
	_cm->AddCharacter(bm);

}

EnemyFactory::~EnemyFactory() {

	//libera todos os recursos.
	for (auto i = _enemies_list.begin(); i != _enemies_list.end(); i++) {
		delete (BaseEnemy*)i->second;
	}

}