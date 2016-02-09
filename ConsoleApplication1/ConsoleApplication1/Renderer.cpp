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

		al_draw_bitmap(s->GetFrameImage(), 0.0, 0.0, 0);
	}

	al_flip_display();

	return true;
}

Renderer::~Renderer() {
	al_destroy_display(_display);
}