#include "CharacterManager.hpp"

CharacterManager::CharacterManager(){}
void CharacterManager::AddCharacter(Character* c){
	fprintf(stderr, "[CharacterManager] Char com id %d adicionado no CharManager\n",
		c->GetID());

	_chars.push_back(c);

}
void CharacterManager::RemoveCharacter(int id){
	fprintf(stderr, "[CharacterManager] Char com id %d a ser removido\n", id);


	for (auto i = _chars.begin();
		i != _chars.end();
		++i) {
		
		if ((*i)->GetID() == id) {
			fprintf(stderr, "[CharacterManager] Char com id %d removido\n", id);
			_chars.erase(i);
			return;
		}

	}

}