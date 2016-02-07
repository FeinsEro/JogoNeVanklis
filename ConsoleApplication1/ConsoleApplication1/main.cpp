#include <stdio.h>

//Includes do Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "EventQueue.hpp"

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;

	if (!al_init()) {
		fprintf(stderr, "Falha em iniciar saporra");
		return -1;
	}

	display = al_create_display(640, 480);
	if (!display) {
		fprintf(stderr, "erro no display");
		return -1;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "Erro ao iniciar suporte a imagens");
		return -1;
	}

	EventQueue ev(display);

	while (ev.CheckEvents()) {

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();

		al_rest(0.1);
	}
	al_destroy_display(display);

	return 0;
}
