#pragma once
#include <string>
#include <vector>

#include <allegro5\allegro.h>

#include "Sprite.hpp"
#include "Item.hpp"
#include "Map.hpp"

#define TYPEID_PLAYER 0

class Character {
protected:
	float _XPos, _YPos;

	static int lastID;

	std::string _name;
	unsigned int _xp;
	unsigned int _HP, _ATK, _DEF, _labia, _dinheiro, _medo, _sanidade, _armadura;
	unsigned int _mana, _atkdemon, _defdemon;
	
	int _ID;

	//Id de tipo. Vai ser usada pelo CharFactory para criar os objetos 
	int _TypeID; 

	std::vector<Item*> _items;

	Sprite* _sprite;
public:


	inline int GetTypeID() { return _TypeID; }

	inline std::string GetName() { return this->_name; }
	inline void SetName(std::string name) { this->_name = name; }

	inline void GetXP(unsigned int& xp) { xp = this->_xp; }
	inline void SetXP(unsigned int& xp) { this->_xp = xp; }

	inline void GetPosition(float& x, float& y) { x = this->_XPos; y = this->_YPos; }
	inline void SetPosition(float& x, float& y) { this->_XPos = x; this->_YPos = y; }
	inline void GetHP(unsigned int& HP) { HP = this->_HP; }
	inline void SetHP(unsigned int& HP) { this->_HP = HP; }
	inline void GetATK(unsigned int& ATK) { ATK = this->_ATK; }
	inline void SetATK(unsigned int& ATK) { this->_ATK = ATK; }
	inline void GetDEF(unsigned int& DEF) { DEF = this->_DEF; }
	inline void SetDEF(unsigned int& DEF) { this->_DEF = DEF; }
	inline void GetLabia(unsigned int& labia) { labia = this->_labia; }
	inline void SetLabia(unsigned int& labia) { this->_labia = labia; }
	inline void GetDinheiro(unsigned int& dinheiro) { dinheiro = this->_dinheiro; }
	inline void SetDinheiro(unsigned int& dinheiro) { this->_dinheiro = dinheiro; }
	inline void GetMedo(unsigned int& medo) { medo = this->_medo; }
	inline void SetMedo(unsigned int& medo) { this->_medo = medo; }
	inline void GetSanidade(unsigned int& sanidade) { sanidade = this->_sanidade; }
	inline void SetSanidade(unsigned int& sanidade) { this->_sanidade = sanidade; }

	inline void GetArmadura(unsigned int& armadura) { armadura = this->_armadura; }
	inline void SetArmadura(unsigned int& armadura) { this->_armadura = armadura; }
	inline void GetMana(unsigned int& mana) { mana = this->_mana; }
	inline void SetMana(unsigned int& mana) { this->_mana = mana; }
	inline void GetAtkDemon(unsigned int& atkdemon) { atkdemon = this->_atkdemon; }
	inline void SetAtkDemon(unsigned int& atkdemon) { this->_atkdemon = atkdemon; }
	inline void GetDefDemon(unsigned int& defdemon) { defdemon = this->_defdemon; }
	inline void SetDefDemon(unsigned int& defdemon) { this->_defdemon = defdemon; }

	inline void GetSprite(Sprite** s) { *s = _sprite; }
	inline void SetSprite(Sprite* s) { _sprite = s; }
	
	void AddItem(Item* i);
	void RemoveItem(int itemID);
	Item* GetItem(int itemID);

	inline void GetAllItems(std::vector<Item*>** list) { *list = &_items; }

	inline int GetID() { return _ID; }

	virtual std::string Falar() = 0;
	virtual void Andar(float deltax, float deltay) = 0;
	virtual void Lutar() = 0;
	virtual void DoEvents(void* charmanager, Map* map) = 0;
	virtual void Reviver() = 0;

	virtual Character* Clone(float x, float y) { return NULL; }


	Character(Sprite* s = NULL, unsigned int XP = 0, 
		unsigned int XPos = 0, unsigned int YPos = 0, std::string name = "",
		unsigned int HP = 0, unsigned int dinheiro = 0, unsigned int ATK = 0, unsigned int DEF = 0,
		unsigned int labia = 0, unsigned int medo = 0, unsigned int sanidade = 0,
		unsigned int armadura = 0, unsigned int mana = 0, unsigned int atkdemon = 0,
		unsigned int defdemon = 0);

};