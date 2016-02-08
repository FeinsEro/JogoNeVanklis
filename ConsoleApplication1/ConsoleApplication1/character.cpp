#include "Character.hpp"
#include <string>

static int lastID = 0;

Character::Character(unsigned int XPos, unsigned int YPos, std::string name,
	unsigned int HP, unsigned int dinheiro, unsigned int ATK, 
	unsigned int DEF, unsigned int labia, unsigned int medo, unsigned sanidade)
{
	this->_XPos = XPos;
	this->_YPos = YPos;
	this->_name = name;
	this->_dinheiro = dinheiro;
	this->_ATK = ATK;
	this->_DEF = DEF;
	this->_labia = labia;
	this->_medo = medo;
	this->_sanidade = sanidade;
	
	this->_ID = lastID++;

	fprintf(stderr, "[Character] Char \"%s\" (id %d) criado em (%d, %d)\n",
		name.c_str(), _ID, XPos, YPos);
	fprintf(stderr, "[Character] \t dinheiro: %d, atk: %d, def: %d\n",
		dinheiro, ATK, DEF);
	fprintf(stderr, "[Character] \t lábia: %d, medo: %d, sanidade: %d\n",
		labia, medo, sanidade);
}