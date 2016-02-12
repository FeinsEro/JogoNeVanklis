#include "BaseEnemy.hpp"

BaseEnemy::BaseEnemy(BaseEnemy& b, unsigned int x, unsigned int y) : Character() {
	this->_XPos = x;
	this->_YPos = y;
	this->_name = b._name;
	this->_dinheiro = b._dinheiro;
	this->_ATK = b._ATK;
	this->_DEF = b._DEF;
	this->_labia = b._labia;
	this->_medo = b._medo;
	this->_sanidade = b._sanidade;

	this->_sprite = b._sprite;

	this->_armadura = b._armadura;
	this->_mana = b._mana;
	this->_atkdemon = b._atkdemon;
	this->_defdemon = b._defdemon;

	this->_xp = b._xp;

}