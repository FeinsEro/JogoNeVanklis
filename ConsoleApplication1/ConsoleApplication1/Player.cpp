#pragma once

#include "CharacterManager.hpp"
#include "Player.hpp"

Player::Player(unsigned int x, unsigned int y, const char* name) : Character(NULL, 0, x, y, std::string(name),
	100, 0, 0, 0, 0, 0, 0){

	this->_TypeID = TYPEID_PLAYER;
}


int framestop = -1;

float angle;

void Player::DoEvents(void* cm, Map* map) {
	auto charm = (CharacterManager*)cm;
	
	Character* c = charm->GetNearestCharacter(this, angle);

	//fprintf(stderr, "[Player] Ângulo: %.1f graus\n", angle);
	
}


void Player::Andar(int deltax, int deltay) {
	
	if (deltax == 0 && deltay == 0) {
		this->_sprite->SetFrame(framestop);
		this->_sprite->NextFrame();
	}

	int fn;
	if (deltay != 0) {
		fn = this->_sprite->GetFrameNumber();

		if (deltay > 0) {
			//Descendo
			angle = 180;
			if (fn < 1 || fn >= 2) {
				this->_sprite->SetFrame(0);
			}

			framestop = -1;
		}
		else {
			//Subindo
			angle = 0;
			if (fn < 8 || fn >= 9) {
				this->_sprite->SetFrame(7);
			}

			framestop = 6;

		}
		this->_sprite->NextFrame();		
	}

	if (deltax != 0) {
		if (deltax < 0) {
			//Esquerda
			fn = this->_sprite->GetFrameNumber();

			angle = 270;
			if (fn < 3 || fn >= 4) {
				this->_sprite->SetFrame(2);
			}

			framestop = 2;
				
			this->_sprite->NextFrame();		
		} else {
			//Direita
			fn = this->_sprite->GetFrameNumber();

			angle = 90;
			if (fn < 5 || fn >= 6) {
				this->_sprite->SetFrame(4);
			}

			framestop = 4;
			this->_sprite->NextFrame();
		}
	}
}