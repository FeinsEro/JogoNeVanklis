#pragma once

#include <vector>
#include <stdexcept>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "CharacterManager.hpp"

class Renderer {
private:
	ALLEGRO_DISPLAY* _display;
	int _screenw, _screenh; //Tamanho da tela

	int _screenx, _screeny; //Onde a tela está (em relação ao jogo)
	float _unitsize; //Quantos pixels são necessários para 1 unidade no jogo?
	
	CharacterManager* _cm;
public:
	/* Inicializa o renderer
		w e h: Largura e altura da tela */
	Renderer(int w, int h);

	inline void SetCharManager(CharacterManager* cm) { _cm = cm; }
	inline CharacterManager* GetCharManager() { return _cm; }

	inline ALLEGRO_DISPLAY* GetDisplay() { return _display; }

	/* Renderiza um frame. */
	bool Render();

	~Renderer();

};