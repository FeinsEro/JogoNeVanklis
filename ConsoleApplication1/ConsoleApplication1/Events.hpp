#pragma once
#include <string>
#include <allegro5\allegro.h>

	//Controla todos os eventos do jogo. Desde um click do mouse até a movimentação do jogador.
class Events {
public:
	int create_event_queue() {
		ALLEGRO_EVENT_QUEUE *event_queue = NULL;
		event_queue = al_create_event_queue();
		if (!event_queue) {
			return -1;
		}
		al_register_event_source(event_queue, al_get_display_event_source(display));
	}
};