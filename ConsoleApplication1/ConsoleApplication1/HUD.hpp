#pragma once

/* Classe de criação do HUD */

#include <allegro5/bitmap.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "Player.hpp"

class HUD {
private:
	Player* _p;
	ALLEGRO_BITMAP* _bHUD;


public:
	HUD(Player* p);

	ALLEGRO_BITMAP* Draw(ALLEGRO_DISPLAY* d);

};