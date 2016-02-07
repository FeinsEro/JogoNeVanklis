#include "Character.hpp"
#include <string>


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

}