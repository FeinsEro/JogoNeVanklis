#include "CharFactory.hpp"

CharFactory::CharFactory(CharacterManager* cm) {
	_cm = cm;
	_enemies_list = std::map<int /*typeid*/, Character*>();
}

void CharFactory::RegisterCharacter(int type_id, Character* char_instance) {
	_enemies_list.insert(std::pair<int, Character*>(type_id, char_instance));
}
Character* CharFactory::PutCharacter(int type_id, unsigned int x, unsigned int y) {
	try { return _enemies_list.at(type_id)->Clone(x, y); }
	catch (...) { return NULL; }
}

Character* CharFactory::PutCharacter(int type_id, int id, unsigned int x, unsigned int y, int hp) {
	try { 
		Character* ch = _enemies_list.at(type_id)->Clone(x, y); 
		ch->_ID = id;
		ch->_HP = hp;
		return ch;
	}
	catch (...) { return NULL; }
}


CharFactory::~CharFactory() {

}