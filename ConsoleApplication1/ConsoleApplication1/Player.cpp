#pragma once

#include "Player.hpp"

Player::Player(unsigned int x, unsigned int y, const char* name) : Character(NULL, 0, x, y, std::string(name),
	100, 0, 0, 0, 0, 0, 0){

	this->_TypeID = TYPEID_PLAYER;
}


void Player::DoEvents(void* cm, Map* map) {
	
}

int framestop = -1;

void Player::Andar(int deltax, int deltay) {
	
	if (deltax == 0 && deltay == 0) {
		this->_sprite->SetFrame(framestop);
		this->_sprite->NextFrame();
	}

	int fn;
	if (deltay != 0) {
		fn = this->_sprite->GetFrameNumber();

		if (deltay > 0) {
			if (fn < 1 || fn >= 2) {
				this->_sprite->SetFrame(0);
			}

			framestop = -1;
		}
		else {
			if (fn < 8 || fn >= 9) {
				this->_sprite->SetFrame(7);
			}

			framestop = 6;

		}
		this->_sprite->NextFrame();		
	}

	if (deltax != 0) {
		if (deltax < 0) {
			fn = this->_sprite->GetFrameNumber();

			if (fn < 3 || fn >= 4) {
				this->_sprite->SetFrame(2);
			}

			framestop = 2;
				
			this->_sprite->NextFrame();		
		} else {
			fn = this->_sprite->GetFrameNumber();

			if (fn < 5 || fn >= 6) {
				this->_sprite->SetFrame(4);
			}

			framestop = 4;
			this->_sprite->NextFrame();
		}
	}
}