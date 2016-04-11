#pragma once

#include "CharacterManager.hpp"
#include "Player.hpp"
#include "EventQueue.hpp"

float _last_control_update;
float deltax = 0, deltay = 0;
Animation* _anim;


float angle;

Player::Player(unsigned int x, unsigned int y, const char* name) : Character(NULL, 0, x, y, std::string(name),
	100, 0, 0, 0, 0, 0, 0){

	this->_TypeID = TYPEID_PLAYER;
	
	_last_control_update = al_get_time();
	_anim = new Animation(this->_sprite);

	_anim->Add(AnimationProperties("descer", 0, 1 ));
	_anim->Add(AnimationProperties("subir", 7, 8));
	_anim->Add(AnimationProperties("direita", 4, 5));
	_anim->Add(AnimationProperties("esquerda", 2, 3));
	_anim->Add(AnimationProperties("parado", 0, 0));

	angle = 0.0f;
}


int framestop = -1;


EventQueue* _ev;
bool attackOn = false;

void Player::DoEvents(void* cm, Map* map) {
	auto charm = (CharacterManager*)cm;
	printf("You are at %.1fx%.1f ", this->_XPos, this->_YPos);


	if (attackOn){
		Character* c = charm->GetNearestCharacter(this, angle);
		if (c) {
			float fx, fy;
			c->GetPosition(fx, fy);
			printf(", Tried to attack %s (%d) at (%.1fx%.1f)", c->GetName().c_str(), c->GetID(), 
				fx, fy);
			charm->DoFight(this, c);
		}
		else {
			printf("\t\t\t\t\t");
		}
	}

	printf("\r");
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

		case ALLEGRO_KEY_LCTRL:
			if (e.key_status == ButtonStatus::Pressed)
				attackOn = true;
			else if (e.key_status == ButtonStatus::Released)
				attackOn = false;

			break;


		}

		if (cima) { y -= .1; angle = 90; }
		if (baixo) { y += .1; angle = 270; }
		if (direita) { x += .1; angle = 0; }
		if (esquerda) { x -= .1; angle = 180; }

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
	
			//angle = 180;
			_anim->RunAnimation("esquerda");
		}
		else {
			//Direita
			
			//angle = 0;
			_anim->RunAnimation("direita");
		}
		return;
	}

	if (deltay != 0) {
		
		if (deltay > 0) {
			//Descendo
			//angle = 270;
			_anim->RunAnimation("descer");
		}
		else {
			//Subindo
			//angle = 90;
			_anim->RunAnimation("subir");

		}
	}

}