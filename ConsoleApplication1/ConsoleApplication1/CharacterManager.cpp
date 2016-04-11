#include "CharacterManager.hpp"

CharacterManager::CharacterManager(){}

int minZIndex = 1;
void CharacterManager::AddCharacter(Character* c){
	fprintf(stderr, "[CharacterManager] Char com id %d:%d adicionado no CharManager\n",
		c->GetTypeID(), c->GetID());

	Sprite* ns;
	c->GetSprite(&ns);

	//Se for menor, já adiciona
	if (ns->GetZIndex() < minZIndex) {
		minZIndex = ns->GetZIndex();
		_chars.insert(_chars.begin(), c);
		return;
	}

	/*	Ordena os characters por z-index do sprite conforme os adiciona 
		Isso não faz _muita_ diferença na hora de rodar, já que a adição dos 
		chars é feita atualmente no começo (e talvez nem faça muita no final),
		mas já fica no esquema na hora de renderizar */
	for (auto i = _chars.begin();
		i != _chars.end();
		++i) {

		Sprite* s;
		(*i)->GetSprite(&s);
	
		if (s && ns) {
			if (s->GetZIndex() == ns->GetZIndex()) {
				_chars.insert(i, c);
				return;
			}
		}

	}

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
		(*i)->DoEvents(this, _map);
	}
}


/* Mostra o char mais próximo de você, a 'angle' graus.
	0	graus = cima
	90	graus = direita
	180	graus = baixo
	270 graus = esquerda 
	
	360 graus = todos.
	*/

Character* CharacterManager::GetNearestCharacter(Character* c, int angle) {
	float angle_rad = angle * 3.1415f / 180.0f;

	float x, y, w, h;
	c->GetPosition(x, y);

	//1 unidade = 32 pixels
	//Sprites têm 32 pixels (geralmente) = 1 unidades.
	//TODO: Character::Get/SetSize()
	w = 32;
	h = 32;

	Character* destiny = NULL;

	for (auto it = _chars.begin();
	it != _chars.end();
		it++) {
		float destx, desty;
		(*it)->GetPosition(destx, desty);
		Sprite* s;
		(*it)->GetSprite(&s);

		w = (s->GetFrameWidth() / 32.0f) * s->GetZoomFactor();
		h = (s->GetFrameHeight() / 32.0f) * s->GetZoomFactor();

		if (destx >= (x - w) && destx <= (x + w)) {
			if (desty >= (y - h) && desty <= (y + h)) {
				if (c->GetID() != (*it)->GetID()){

					/* Otimizado para ângulos retos
						TODO: Otimizar de 45 em 45, não é necessário agora*/
					bool isOK = false;
					switch (angle) {
					case 0:
						isOK = (destx > x);
						break;
					case 90:
						isOK = (desty > y);
						break;
					case 180:
						isOK = (x > destx);
						break;
					case 270:
						isOK = (y > desty);
						break;
					case 360:
						isOK = true;

					}

					if (isOK)
						destiny = (Character*)(*it);
					



					
				}
			}
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



void CharacterManager::SetPlayer(Player* p) {
	//O player deve ser um character já adicionado (isso evita duplicação de código
	for (auto it = _chars.begin(); it != _chars.end(); it++){
		//O player tem um ID específico.
		if ((*it)->GetID() == p->GetID()) {
			_player = (Player*)(*it);
			return;
		}

	}

	//Não achou? Então adicionamos.
	_chars.push_back(p);
	_player = p;
}
Player* CharacterManager::GetPlayer() {
	return _player;
}