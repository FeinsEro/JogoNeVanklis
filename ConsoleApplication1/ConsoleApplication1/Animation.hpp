#pragma once

/*	Animation
	Define e controla as animações de cada sprite.

	As animações do sprite serão definidas nessa classe, assim é melhor.
	Afinal, cada classe deverá fazer uma coisa, e existem sprites que não 
são animados, como o das árvores.
*/

#include "Sprite.hpp"

#include <cstring> //para strlen e strcpy_s(). 
#include <map>


/*	strcpy_s() é uma viadagem pura, por que não usa strncpy(), Microsoft?
	como todo mundo?
	
	puta merda */
struct AnimationProperties {
	/* O nome da animação */
	char AnimationName[64];

	/* Frames iniciais e finais da animação */
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
	/* Um hash onde as animações serão guardadas */
	std::map<const char*, AnimationProperties> _animationMap;
	Sprite* _sprite;
	int _framecache = -1;

public:
	Animation(Sprite*);

	/*	Pega o nome da animação e retorna um ponteiro para ela
		Se ela não existir, não roda nada.
	*/
	AnimationProperties* Get(const char* name);

	void Add(AnimationProperties);

	/* Roda a animação do sprite inteiro */
	void RunAnimation();
	
	/* Roda uma animação específica */
	void RunAnimation(const char* animation);

	void SetSprite(Sprite*);

	/*	Força com que, na próxima atualização de frame, ele o atualize 
		diretamente do sprite, anulando o cache.
		
		Útil quando você modifica o frame do sprite de fora. 
		Isso não é recomendado. Se você fizer isso, você é um pau no cu */
	void KillCache();
};