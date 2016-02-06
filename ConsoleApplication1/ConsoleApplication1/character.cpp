#include "Character.hpp"
#include <string>


Character::Character(unsigned int XPos = 0, unsigned int YPos = 0, std::string name = "", unsigned int HP = 0, unsigned int dinheiro = 0, unsigned int ATK = 0, unsigned int DEF = 0, unsigned int labia = 0)
{
	this->_XPos = XPos;
	this->_YPos = YPos;
	this->_name = name;
	this->_dinheiro = dinheiro;
	this->_ATK = ATK;
	this->_DEF = DEF;
	this->_labia = labia;

}