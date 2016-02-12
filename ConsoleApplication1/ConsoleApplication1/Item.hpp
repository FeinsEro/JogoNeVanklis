#pragma once

#include <string>

/* Classe genérica para itens */

class Item {
private:
	unsigned int _id;		//id
	unsigned int _value;	//valor em dinheiro
	std::string _name;
	std::string _descricao;
	int _bonusHP, _bonusATK, _bonusDEF, _bonusAMR, _bonusMagicDEF, _bonusLabia; //valores bonus podem ser negativos também.
	int _bonusSanidade; //deixei esses dois separados pra dar uma explicação melhor pra eles.
	int _bonusNoFear; //basicamente, esses valores vão aumentar o quanto o usuário consegue ficar sobre a pressão do mapa e dos monstros sem enlouquecer ou cagar de medo.
	unsigned int _bonusXP; //caso o item aumente a quantidade de xp que o player consegue.
	unsigned int _bonusDinheiro; //caso o item aumente a quantidade de dinheiro que o player consegue.

	Sprite* _sprite; //O sprite usado para desenhar o item;
public:
	inline unsigned int GetID() { return _id; }
	inline unsigned int GetValue() { return _value; }
	inline void GetName(std::string& name) { name = _name; }


	Item(std::string name, std::string descricao, unsigned int value, 
		int bonusHP = 0, int bonusATK = 0, int bonusDEF = 0, int bonusAMR = 0,
		int bonusMagicDEF = 0, int bonusLabia = 0, int bonusSanidade = 0,
		int bonusNoFear = 0, unsigned int bonusXP = 0, unsigned int bonusDinheiro = 0);

	inline void SetSprite(Sprite* s) { _sprite = s; }
	inline void GetSprite(Sprite** s) { *s = _sprite; }
};