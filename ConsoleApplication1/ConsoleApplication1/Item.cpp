#pragma once

#include "Item.hpp"

static unsigned int _lastid = 0;

Item::Item(std::string name, std::string descricao,
	unsigned int value, int bonusHP, int bonusATK,
	int bonusDEF, int bonusAMR, int bonusMagicDEF,
	int bonusLabia, int bonusSanidade, int bonusNoFear,
	unsigned int bonusXP, unsigned int bonusDinheiro) {


	this->_id = _lastid++;
	this->_name = name;
	this->_value = value;
	this->_descricao = descricao;
	this->_bonusHP = bonusHP;
	this->_bonusATK = bonusATK;
	this->_bonusDEF = bonusDEF;
	this->_bonusAMR = bonusAMR;
	this->_bonusMagicDEF = bonusMagicDEF;
	this->_bonusLabia = bonusLabia;
	this->_bonusSanidade = bonusSanidade;
	this->_bonusNoFear = bonusNoFear;
	this->_bonusXP = bonusXP;
	this->_bonusDinheiro = bonusDinheiro;


	fprintf(stderr, "[Item] Item \"%s\" criado, id %d\n", name.c_str(), _id);
	fprintf(stderr, "[Item] \t valor: %d\n", _value);
}