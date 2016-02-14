#include <allegro5\allegro.h>
#include "Events.hpp"
Events::Events() {
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
	if (!event_queue) {
		return -1;
	}
}