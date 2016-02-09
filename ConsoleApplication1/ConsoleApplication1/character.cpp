#include "Character.hpp"
#include <string>

static int lastID = 0;

Character::Character(Sprite* s, unsigned int XP, unsigned int XPos, unsigned int YPos, std::string name,
	unsigned int HP, unsigned int dinheiro, unsigned int ATK, 
	unsigned int DEF, unsigned int labia, unsigned int medo, unsigned sanidade, 
	unsigned int armadura, unsigned int mana, unsigned int atkdemon,
	unsigned int defdemon)
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

	this->_sprite = s;

	this->_armadura = armadura;
	this->_mana = mana;
	this->_atkdemon = atkdemon;
	this->_defdemon = defdemon;

	this->_xp = XP;

	fprintf(stderr, "[Character] Char \"%s\" (id %d) criado em (%d, %d), %d de XP\n",
		name.c_str(), _ID, XPos, YPos, XP);
	fprintf(stderr, "[Character] \t dinheiro: %d, atk: %d, def: %d\n",
		dinheiro, ATK, DEF);
	fprintf(stderr, "[Character] \t l�bia: %d, medo: %d, sanidade: %d, armadura: %d\n",
		labia, medo, sanidade, armadura);
	fprintf(stderr, "[Character] \t mana: %d, atkdemon: %d, defdemon: %d\n",
		mana, atkdemon, defdemon);
}