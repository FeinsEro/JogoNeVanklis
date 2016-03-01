#pragma once

#include <vector>
#include <stdexcept>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "CharacterManager.hpp"
#include "HUD.hpp"

class Renderer {
private:
	ALLEGRO_DISPLAY* _display;
	int _screenw, _screenh; //Tamanho da tela

	HUD* _hud;

	float _screenx, _screeny; //Onde a tela est� (em rela��o ao jogo)
	float _unitsize; //Quantos pixels s�o necess�rios para 1 unidade no jogo?
	
	CharacterManager* _cm;
public:
	/* Inicializa o renderer
		w e h: Largura e altura da tela */
	Renderer(int w, int h);

	inline void SetCharManager(CharacterManager* cm) { _cm = cm; }
	inline CharacterManager* GetCharManager() { return _cm; }

	inline ALLEGRO_DISPLAY* GetDisplay() { return _display; }

	inline HUD* GetHUD() { return _hud; }
	inline void SetHUD(HUD* h) { _hud = h; }

	/* Renderiza um frame. */
	bool Render();

	~Renderer();

};