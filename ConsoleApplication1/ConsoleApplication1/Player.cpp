#pragma once

#include "CharacterManager.hpp"
#include "Player.hpp"
#include "EventQueue.hpp"

Player::Player(unsigned int x, unsigned int y, const char* name) : Character(NULL, 0, x, y, std::string(name),
	100, 0, 0, 0, 0, 0, 0){

	this->_TypeID = TYPEID_PLAYER;
}


int framestop = -1;

float angle;

EventQueue* _ev;

void Player::DoEvents(void* cm, Map* map) {
	auto charm = (CharacterManager*)cm;
	
	Character* c = charm->GetNearestCharacter(this, angle);


}


void Player::Control(Map* map) {
	Event e;

	while (_ev->PopEvent(e)) {
		float x, y;
		x = this->_XPos;
		y = this->_YPos;

		switch (e.keycode) {
		case ALLEGRO_KEY_UP:
			if (e.key_status == ButtonStatus::Pressed)
				cima = true;
			else if (e.key_status == ButtonStatus::Released)
				cima = false;
			break;

		case ALLEGRO_KEY_DOWN:
			if (e.key_status == ButtonStatus::Pressed)
				baixo = true;
			else if (e.key_status == ButtonStatus::Released)
				baixo = false;
			break;

		case ALLEGRO_KEY_LEFT:
			if (e.key_status == ButtonStatus::Pressed)
				esquerda = true;
			else if (e.key_status == ButtonStatus::Released)
				esquerda = false;
			break;

		case ALLEGRO_KEY_RIGHT:
			if (e.key_status == ButtonStatus::Pressed)
				direita = true;
			else if (e.key_status == ButtonStatus::Released)
				direita = false;
			break;

		}

		if (cima) y -= .1;
		if (baixo) y += .1;
		if (direita) x += .1;
		if (esquerda) x -= .1;

		x = max(x, 0);
		y = max(y, 0);

		x = min(x, map->GetWidth() - 1.0);
		y = min(y, map->GetHeight() - 1.0);

		this->_XPos = x;
		this->_YPos = y;
	}
}

void Player::SetEventQueue(void* ev) { _ev = (EventQueue*) ev; }

void Player::Andar(float deltax, float deltay) {
	
	if (deltax == 0 && deltay == 0) {
		this->_sprite->SetFrame(framestop);
		this->_sprite->NextFrame();
	}

	int fn;

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
		}
		else {
			//Direita
			fn = this->_sprite->GetFrameNumber();

			angle = 90;
			if (fn < 5 || fn >= 6) {
				this->_sprite->SetFrame(4);
			}

			framestop = 4;
			this->_sprite->NextFrame();
		}
		return;
	}

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

}