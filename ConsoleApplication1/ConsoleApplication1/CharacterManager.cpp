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

void CharacterManager::DoAllEvents() {
	for (auto i = _chars.begin();
	i != _chars.end();
		++i) {
		(*i)->DoEvents(this, NULL);
	}
}


/* Mostra o char mais próximo de você, a 'angle' graus.
	0	graus = cima
	90	graus = direita
	180	graus = baixo
	270 graus = esquerda 
	
	Atualmente, 'angle' não faz efeito.
	*/

Character* CharacterManager::GetNearestCharacter(Character* c, int angle) {
	unsigned int x, y, w, h;
	c->GetPosition(x, y);

	//1 unidade = 4 pixels
	//Sprites têm 32 pixels (geralmente) = 8 unidades.
	//TODO: Character::Get/SetSize()
	w = 8;
	h = 8;

	Character* destiny = NULL;

	for (auto it = _chars.begin();
	it != _chars.end();
		it++) {
		unsigned int destx, desty;
		(*it)->GetPosition(destx, desty);
		Sprite* s;
		(*it)->GetSprite(&s);

		w = 8 * s->GetZoomFactor();
		h = 8 * s->GetZoomFactor();

		if (destx > (x - 2 * w) && destx < (x + 2 * w)) {

			if (c->GetID() != (*it)->GetID())
				destiny = (Character*)(*it);
		}

		if (desty >(y - 2 * h) && desty < (y + 2 * h)) {
			if (c->GetID() != (*it)->GetID())
				destiny = (Character*)(*it);
		}

		

	}

	return destiny;
}


Character * CharacterManager::GetNearestCharacterInRange(Character* c, float angle, int range)
{
	return NULL;
}

void  CharacterManager::DoFight(Character* attacker, Character* defender) {

	//Pega todos os itens de ataque do atacante
	std::vector<Item*>* itens;
	attacker->GetAllItems(&itens);

	int atkbonus = 0, defbonus = 0;

	for (auto it = itens->begin();
	it != itens->end();
		it++) {
		atkbonus += (*it)->GetATKBonus();
	}

	int atk = 0;
	attacker->GetATK((unsigned int&) atk);
	atk += atkbonus;

	//Pega todos os itens de defesa do defensor
	defender->GetAllItems(&itens);

	for (auto it = itens->begin();
	it != itens->end();
		it++) {
		defbonus += (*it)->GetDEFBonus();
	}

	int def = 0;
	defender->GetDEF((unsigned int&)atk);
	def += defbonus;

	unsigned int hp;
	defender->GetHP(hp);
	hp -= (atk - def);
	defender->SetHP(hp);
}
