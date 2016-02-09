#include "Renderer.hpp"

/* Inicializa o renderer
w e h: Largura e altura da tela */
Renderer::Renderer(int w, int h) {
	_display = NULL;

	if (!al_init()) {
		throw std::runtime_error("Falha em iniciar saporra");
	}

	_display = al_create_display(w, h);
	if (!_display) {
		throw std::runtime_error("erro no display");
	}

	if (!al_init_image_addon()) {
		throw std::runtime_error("Erro ao iniciar suporte a imagens");
	}

	fprintf(stderr, "[Renderer] Renderer criado. Resolução: %dx%d\n", w, h);

	_screenx = 0;
	_screeny = 0;

	_screenw = w;
	_screenh = h;

	_unitsize = 4.0; //4 pixels = 1 unidade
}

/* Renderiza um frame. */
bool Renderer::Render() {

	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	std::vector<Character*> characters;
	_cm->GetAllChars(&characters);

	//Renderiza os sprites dos characters nas posições que eles estão
	for (auto sp_iter = characters.begin();
		sp_iter != characters.end();
		++sp_iter) {
			
		Character* c = *sp_iter;
		Sprite* s;
		c->GetSprite(&s);

		if (!s) continue;

		int gamex, gamey;
		c->GetPosition((unsigned int&)gamex, (unsigned int&)gamey);


		ALLEGRO_BITMAP* bm_sprite = s->GetFrameImage();

		if (_screenx > (gamex + (al_get_bitmap_width(bm_sprite)/_unitsize))) {
			//Não dá nem pra ver o personagem
			continue;
		}

		if ((_screenx)+(_screenw / _unitsize) < gamex) {
			//A tela está antes do personagem
			continue;
		}


		float drawx = (gamex - _screenx) * _unitsize;
		float drawy = (gamey - _screeny) * _unitsize;

		al_draw_bitmap(bm_sprite, drawx, drawy, 0);
	}

	al_flip_display();

	return true;
}

Renderer::~Renderer() {
	al_destroy_display(_display);
}