#pragma once

#include <string>

/* Classe gen�rica para itens */

class Item {
private:
	unsigned int _id;		//id
	unsigned int _value;	//valor em dinheiro
	std::string _name;
	std::string _descricao;
	int _bonusHP, _bonusATK, _bonusDEF, _bonusAMR, _bonusMagicDEF, _bonusLabia; //valores bonus podem ser negativos tamb�m.
	int _bonusSanidade; //deixei esses dois separados pra dar uma explica��o melhor pra eles.
	int _bonusNoFear; //basicamente, esses valores v�o aumentar o quanto o usu�rio consegue ficar sobre a press�o do mapa e dos monstros sem enlouquecer ou cagar de medo.
	unsigned int _bonusXP; //caso o item aumente a quantidade de xp que o player consegue.
	unsigned int _bonusDinheiro; //caso o item aumente a quantidade de dinheiro que o player consegue.

public:
	inline unsigned int GetID() { return _id; }

	inline unsigned int GetValue() { return _value; }

	inline void GetName(std::string& name) { name = _name; }


	Item(std::string name, std::string descricao, unsigned int value, int bonusHP, int bonusATK, int bonusDEF, int bonusAMR, int bonusMagicDEF, int bonusLabia, int bonusSanidade, int bonusNoFear, unsigned int bonusXP, unsigned int bonusDinheiro);

};