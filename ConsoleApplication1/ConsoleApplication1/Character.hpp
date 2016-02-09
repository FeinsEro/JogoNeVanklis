#pragma once
#include <string>
#include <allegro5\allegro.h>

#include "Sprite.hpp"

class Character {
protected:
	unsigned int _XPos, _YPos;


	std::string _name;
	unsigned int _HP, _ATK, _DEF, _labia, _dinheiro, _medo, _sanidade;
	int _ID;

	Sprite* _sprite;
public:
	inline std::string GetName() { return this->_name; }
	inline void SetName(std::string name) { this->_name = name; }

	inline void GetPosition(unsigned int& x, unsigned int& y) { x = this->_XPos; y = this->_YPos; }
	inline void SetPosition(unsigned int& x, unsigned int& y) { this->_XPos = x; this->_YPos = y; }

	inline void GetSprite(Sprite** s) { *s = _sprite; }
	inline void SetSprite(Sprite* s) { _sprite = s; }

	inline int GetID() { return _ID; }

	virtual void Falar() = 0;
	virtual void Andar() = 0;
	virtual void Lutar() = 0;
	virtual void DoEvents() = 0;
	virtual void Reviver() = 0;

	Character(Sprite* s = NULL, unsigned int XPos = 0, unsigned int YPos = 0, std::string name = "",
		unsigned int HP = 0, unsigned int dinheiro = 0, unsigned int ATK = 0, unsigned int DEF = 0, 
		unsigned int labia = 0, unsigned int medo = 0, unsigned int sanidade = 0);

};