#pragma once

#include "Player.hpp"

Player::Player(unsigned int x, unsigned int y, const char* name) : Character(NULL, 0, x, y, std::string(name),
	100, 0, 0, 0, 0, 0, 0){

	this->_TypeID = TYPEID_PLAYER;
}


void Player::DoEvents(void* cm, TileMap* map) {
	
}

void Player::Andar() {
	//Atualiza a anima��o
	this->_sprite->NextFrame();
}