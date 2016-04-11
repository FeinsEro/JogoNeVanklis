#include "Animation.hpp"

Animation::Animation(Sprite* s) {
	this->_sprite = s;
}

AnimationProperties* Animation::Get(const char* name) {
	/*	Verifica se a hash existe 
		Se formos verificar puramente usando if (hash[name]), a STL irá criar um elemento, 
		e eu não quero isso */

	for (auto it = _animationMap.begin();
		it != _animationMap.end();
		++it) {

		if (!strcmp(name, it->first)) {
			return &it->second;
		}

	}

	return NULL;

}

void Animation::Add(AnimationProperties props) {
	char* name = new char[strlen(props.AnimationName)+1];
	strcpy_s(name, strlen(props.AnimationName)+1, props.AnimationName);

	_animationMap[name] = props;
	_animationMap[name].animation = this;
}

/* Roda a animação do sprite inteiro */
void Animation::RunAnimation() {
	if (_framecache < 0) {
		_framecache = _sprite->GetFrameNumber();
	}

	_sprite->NextFrame();
	_framecache++;
}

/* Roda uma animação específica */
void Animation::RunAnimation(const char* animation) {
	if (_framecache < 0) {
		_framecache = _sprite->GetFrameNumber();
	}

	int minFrame, maxFrame;
	AnimationProperties* props = this->Get(animation);
	if (!props) {
		return;
	}

	minFrame = props->startFrame;
	maxFrame = props->endFrame;

	if (_framecache > maxFrame || _framecache < minFrame ) {
		_framecache = minFrame;
		_sprite->SetFrame(_framecache);
	}

	//printf("%d\n", _framecache);
	_framecache++;
	_sprite->NextFrame(false);
}

void Animation::SetSprite(Sprite* s) {
	this->_sprite = s;
}

void AnimationProperties::Run() {
	((Animation*)animation)->RunAnimation(AnimationName);
}

void Animation::KillCache() {
	_framecache = -1;
}