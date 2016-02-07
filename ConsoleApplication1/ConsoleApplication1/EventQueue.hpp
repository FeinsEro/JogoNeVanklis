#pragma once

/* Fila de eventos para o jogo */

struct Event {
	int mouse_x, mouse_y;  //Posi��o (EM PIXEL) do cursor do mouse
	int mouse_button;  //Bot�es do mouse pressionados (0x01 = esquerdo, 0x02 = direito, 0x04= meio)
	int mouse_status; //Estado do bot�o do mouse: N�o pressionado, bot�o foi pressionado e bot�o foi solto
	int keycode; //C�digo (scancode) da tecla pressionada
	char keyletter; //O caractere que essa tecla representa
	int alt_keys; //Dead keys pressionadas: 0x01 - ctrl, 0x02 - alt, 0x04 - shift;
	int key_status; //Estado da tecla: N�o pressionada, pressionada e solta.
};

enum MouseButton {
	//Seu mouse � um Razer com 10 bot�es? Pau no seu cu! O jogo s� usa tr�s.
	Left = 0x01, Right = 0x02, Middle = 0x04
};

enum ButtonStatus {
	//Serve pra mouse_status e pra key_status.
	NoEvent = 0x0, Pressed = 0x1, Released = 0x2, Repeat = 0x3
};

enum AltKeys {
	Ctrl = 0x01, Alt = 0x02, Shift = 0x04
};

/* A classe que cuida da event queue */
#include <queue> //std::queue
#include <allegro5/keyboard.h> 
#include <allegro5/mouse.h>
#include <allegro5/display.h>

/*	Tamanho m�ximo da fila antes que o jogo comece a retirar os primeiros elementos inseridos 
	Sem isso, algum filho da puta poderia facilmente encher a mem�ria de eventos */
#define MAX_QUEUE_SIZE 1500


class EventQueue {
private:
	std::queue<Event> _events;

	ALLEGRO_EVENT_QUEUE* _allegro_queue;
public:
	//Construtor
	//POR FAVOR MUDE PARA A CLASSE RENDERER QUANDO ELA ESTIVER PRONTA. EU QUERO A API DO ALLEGRO BEM ENCAPSULADA
	EventQueue(ALLEGRO_DISPLAY* d);

	//Verifica se h� eventos e preenche a event queue.
	//Retorna false se recebe um evento que provoque a sa�da do jogo
	bool CheckEvents();

	//Obt�m o primeiro evento da fila. Retorna false se n�o houverem mais eventos, caso contr�rio retorna true.
	bool GetEvent(Event& e);

	//Obt�m o primeiro evento da fila, e o retira da mesma.
	//Retorna false se n�o houverem mais eventos, caso contr�rio retorna true.
	bool PopEvent(Event& e);

};