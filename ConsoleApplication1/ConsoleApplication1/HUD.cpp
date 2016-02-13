#include "HUD.hpp"

ALLEGRO_FONT* _default_font;

HUD::HUD(Player* p) {
	_p = p;
	
	//Necessário para o HUD
	al_init_font_addon();
	
	if (!al_init_ttf_addon()) {
		throw std::runtime_error("Não foi possível iniciar suporte a fontes");
	}

	_default_font = al_load_font("C:\\Windows\\Fonts\\consola.ttf", 16, 0);

	if (!_default_font) {
		throw std::runtime_error("Fonte não encontrada! ");
	}
}

ALLEGRO_BITMAP* HUD::Draw(ALLEGRO_DISPLAY* d) {
	
	_bHUD = al_create_bitmap(al_get_display_width(d), 30);

	al_set_target_bitmap(_bHUD);

	al_draw_filled_rectangle(0, 0, al_get_display_width(d), 30,
		al_map_rgba(0, 0, 0, 128));
	
	//Desenha a quantidade de vida e o nome do personagem (só um exemplo)
	al_draw_text(_default_font, al_map_rgb(0xff, 0xff, 0xff), 10, 10, 0, _p->GetName().c_str());

	char num_str[5];
	unsigned int hp; _p->GetHP(hp);
	sprintf_s(&num_str[0], 5, "%d", hp);
	al_draw_text(_default_font, al_map_rgb(0x00, 0xff, 0xff), (al_get_display_width(d)) - 100, 10, 0,
		num_str);

	al_set_target_bitmap(al_get_backbuffer(d));
	return _bHUD;
}
