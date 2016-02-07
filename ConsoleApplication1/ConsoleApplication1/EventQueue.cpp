#include "EventQueue.hpp"

EventQueue::EventQueue(ALLEGRO_DISPLAY* d) {
	//Obtém a event queue do Allegro, a registra e a torna default
	//Nós vamos obter nossos eventos a partir dela
	_allegro_queue = al_create_event_queue();

	// Inicia os subsistemas de teclado e mouse do Allegro
	al_install_keyboard();
	al_install_mouse();

	//Registra para receber eventos do display, do mouse e do teclado
	al_register_event_source(_allegro_queue,
		al_get_display_event_source(d));
	al_register_event_source(_allegro_queue,
		al_get_mouse_event_source());
	al_register_event_source(_allegro_queue,
		al_get_keyboard_event_source());

}

//Verifica se há eventos e preenche a event queue.
//Retorna false se recebe um evento que provoque a saída do jogo
bool EventQueue::CheckEvents() {
	ALLEGRO_TIMEOUT timeout;
	ALLEGRO_EVENT ev;

	//10 ms de timeout para obter os eventos
	al_init_timeout(&timeout, 0.01);

	while (al_wait_for_event_until(_allegro_queue, &ev, &timeout)) {
		/* Por enquanto apenas trataremos eventos de mouse e de teclado */
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			return false;

		Event e = { 0 };

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN || 
			ev.type == ALLEGRO_EVENT_KEY_UP ){
	
			e.keycode = ev.keyboard.keycode;
			e.keyletter = ((char)ev.keyboard.unichar & 0xff);

			switch (ev.type) {
			case ALLEGRO_EVENT_KEY_DOWN:
				e.key_status = ButtonStatus::Pressed;

				break;
			case ALLEGRO_EVENT_KEY_UP:
				e.key_status = ButtonStatus::Released;

				break;
			}

		} else {
			e.key_status = ButtonStatus::NoEvent;
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ||
			ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP || 
			ev.type == ALLEGRO_EVENT_MOUSE_AXES ) {
			e.mouse_x = ev.mouse.x;
			e.mouse_y = ev.mouse.y;

			e.mouse_button = ev.mouse.button;
		
			switch (ev.type) {
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				e.mouse_status = ButtonStatus::Pressed;

				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				e.mouse_status = ButtonStatus::Released;

				break;
			default:
				e.mouse_status = ButtonStatus::NoEvent;
				break;
			}

		} else {
			e.mouse_button = 0;
		}

		fprintf(stderr, "[EventQueue] Evento inserido: ");
		fprintf(stderr, "[EventQueue]\tTecla %c (scancode %d), keystatus %d\n ",
			e.keyletter, e.keycode, e.key_status);
		fprintf(stderr, "[EventQueue]\tPosição do mouse: (%d, %d), botão %d, mousestatus %d\n",
			e.mouse_x, e.mouse_y, e.mouse_button, e.mouse_status);

		//Insere o evento na fila
		_events.push(e);
	}
}

//Obtém o primeiro evento da fila. Retorna false se não houverem mais eventos, caso contrário retorna true.
bool EventQueue::GetEvent(Event& e) {
	if (!_events.empty()) {
		e = _events.front();
		return true;
	}
	return false;
}

//Obtém o primeiro evento da fila, e o retira da mesma.
//Retorna false se não houverem mais eventos, caso contrário retorna true.
bool EventQueue::PopEvent(Event& e) {
	if (!_events.empty()) {
		e = _events.front();
		_events.pop();
		return true;
	}
	return false;
}