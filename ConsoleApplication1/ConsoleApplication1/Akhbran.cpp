#include "Akhbran.hpp"

Animation* aniAkhbran = NULL;

Akhbran::Akhbran(unsigned int x, unsigned int y) : Character(NULL, 0, x, y, "Akhbran",
	100, 0, 0, 0, 0, 0, 0) {
	this->_sprite = new Sprite("..\\characters\\ahkbran_mov.png", 1.1f, 2);

	aniAkhbran = new Animation{ this->_sprite };
	aniAkhbran->Add(AnimationProperties("direita", -1, 0));
	aniAkhbran->Add(AnimationProperties("esquerda", 1, 2));

	this->_TypeID = TYPEID_AKHBRAN;
	_angle = 180;
}


void Akhbran::DoEvents(void* cm, Map* map) {
	CharacterManager* cManager = (CharacterManager*)cm;

	/* Atualiza a posição de Akhbran para ficar à esquerda do player*/

	Player* p = cManager->GetPlayer();

	if (!p) return;

	float nX, nY;
	p->GetPosition(nX, nY);
	nX += 1.5;
	nY -= 1;

	this->_XPos = max(nX, 0);
	this->_YPos = max(nY, 0);
	this->_XPos = min(this->_XPos, cManager->GetMap()->GetWidth());

	_angle = p->GetAngle();

}

void Akhbran::Andar(float, float) {
	if (_angle >= 0 && _angle < 180)
		aniAkhbran->RunAnimation("direita");
	else
		aniAkhbran->RunAnimation("esquerda");



}

std::string Akhbran::Falar() {
	return "Pega a tampa ae JC";
}

int Akhbran::GetAngle() {
	return _angle;
}