#pragma once

#include "CharacterManager.hpp"
#include "Player.hpp"
#include "EventQueue.hpp"

float _last_control_update;
float deltax = 0, deltay = 0;
Animation* _anim;

Player::Player(unsigned int x, unsigned int y, const char* name) : Character(NULL, 0, x, y, std::string(name),
	100, 0, 0, 0, 0, 0, 0){

	this->_TypeID = TYPEID_PLAYER;
	
	_last_control_update = al_get_time();
	_anim = new Animation(this->_sprite);

	_anim->Add(AnimationProperties("descer", 1, 2 ));
	_anim->Add(AnimationProperties("subir", 8, 9));
	_anim->Add(AnimationProperties("direita", 5, 6));
	_anim->Add(AnimationProperties("esquerda", 3, 4));
	_anim->Add(AnimationProperties("parado", 0, 0));
}


int framestop = -1;

float angle;

EventQueue* _ev;

void Player::DoEvents(void* cm, Map* map) {
	auto charm = (CharacterManager*)cm;
	
	Character* c = charm->GetNearestCharacter(this, angle);

}

void Player::SetSprite(Sprite* s ) {
	Character::SetSprite(s);
	_anim->SetSprite(s);
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

		deltax = x - this->_XPos;
		deltay = y - this->_YPos;

		this->_XPos = x;
		this->_YPos = y;
	}
}

void Player::SetEventQueue(void* ev) { _ev = (EventQueue*) ev; }

void Player::Andar(float a, float b) {
	
	/* if (deltax == 0 && deltay == 0) {
		_anim->RunAnimation("parado");
		return;
	} */

	if (deltax != 0) {
		if (deltax < 0) {
			//Esquerda
			
			angle = 270;
			_anim->RunAnimation("esquerda");
		}
		else {
			//Direita
			
			angle = 90;
			_anim->RunAnimation("direita");
		}
		return;
	}

	if (deltay != 0) {
		
		if (deltay > 0) {
			//Descendo
			angle = 180;
			_anim->RunAnimation("descer");
		}
		else {
			//Subindo
			angle = 0;
			_anim->RunAnimation("subir");

		}
	}

}