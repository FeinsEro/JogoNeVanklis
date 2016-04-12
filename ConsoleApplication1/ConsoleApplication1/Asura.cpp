#include "Asura.hpp"

Animation* aniAsura = NULL;

Asura::Asura(unsigned int x, unsigned int y) : Character(NULL, 0, x, y, "Asura",
	100, 0, 0, 0, 0, 0, 0) {
	this->_sprite = new Sprite("..\\characters\\asura_mov.png", 1.1f, 2);
	
	aniAsura = new Animation{ this->_sprite };
	aniAsura->Add(AnimationProperties("direita", -1, 0));
	aniAsura->Add(AnimationProperties("esquerda", 1, 2));
	
	this->_TypeID = TYPEID_ASURA;
	_angle = 0;
}


void Asura::DoEvents(void* cm, Map* map) {
	CharacterManager* cManager = (CharacterManager*)cm;

	/* Atualiza a posição de Asura para ficar à esquerda do player*/

	Player* p = cManager->GetPlayer();


	if (!p) return;

	float nX, nY;
	p->GetPosition(nX, nY);
	nX -= 1.5;
	nY -= 1;

	this->_XPos = max(nX, 0);
	this->_YPos = max(nY, 0);

	_angle = p->GetAngle();
	
}

void Asura::Andar(float, float) {
	if (_angle >= 0 && _angle < 180)
		aniAsura->RunAnimation("direita");
	else
		aniAsura->RunAnimation("esquerda");



}

std::string Asura::Falar() {
	return "Pega a tampa ae JC";
}

int Asura::GetAngle() {
	return _angle;
}