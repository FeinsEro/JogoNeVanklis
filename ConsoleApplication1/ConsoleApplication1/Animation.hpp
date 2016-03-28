#pragma once

/*	Animation
	Define e controla as anima��es de cada sprite.

	As anima��es do sprite ser�o definidas nessa classe, assim � melhor.
	Afinal, cada classe dever� fazer uma coisa, e existem sprites que n�o 
s�o animados, como o das �rvores.
*/

#include "Sprite.hpp"

#include <cstring> //para strlen e strcpy_s(). 
#include <map>


/*	strcpy_s() � uma viadagem pura, por que n�o usa strncpy(), Microsoft?
	como todo mundo?
	
	puta merda */
struct AnimationProperties {
	/* O nome da anima��o */
	char AnimationName[64];

	/* Frames iniciais e finais da anima��o */
	unsigned int startFrame, endFrame;

	void* animation;

	AnimationProperties(const char* name, int start, int end) {
		int namesize = strlen(name);
		strcpy_s(AnimationName, (namesize > 64) ? 64 : namesize+1, name);
		startFrame = start;
		endFrame = end;
	}

	AnimationProperties() {
		strcpy_s<64>(AnimationName, "");
		startFrame = 0;
		endFrame = -1;
	}

	void Run();
};

class Animation {
private:
	/* Um hash onde as anima��es ser�o guardadas */
	std::map<const char*, AnimationProperties> _animationMap;
	Sprite* _sprite;
	int _framecache = -1;

public:
	Animation(Sprite*);

	/*	Pega o nome da anima��o e retorna um ponteiro para ela
		Se ela n�o existir, n�o roda nada.
	*/
	AnimationProperties* Get(const char* name);

	void Add(AnimationProperties);

	/* Roda a anima��o do sprite inteiro */
	void RunAnimation();
	
	/* Roda uma anima��o espec�fica */
	void RunAnimation(const char* animation);

	void SetSprite(Sprite*);

	/*	For�a com que, na pr�xima atualiza��o de frame, ele o atualize 
		diretamente do sprite, anulando o cache.
		
		�til quando voc� modifica o frame do sprite de fora. 
		Isso n�o � recomendado. Se voc� fizer isso, voc� � um pau no cu */
	void KillCache();
};