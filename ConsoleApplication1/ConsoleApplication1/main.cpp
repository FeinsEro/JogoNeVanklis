#include <stdio.h>

//Includes do Allegro

#include "CharacterManager.hpp"
#include "EventQueue.hpp"
#include "Renderer.hpp"

int main(int argc, char **argv) {

	Renderer* r;
	try {
		r = new Renderer(640, 480);
	}
	catch (std::runtime_error& e) {
		MessageBoxA(NULL, e.what(), "Um erro ocorreu", MB_ICONERROR);
		return -1;
	}
	
	EventQueue ev(r);
	
	CharacterManager cm;
	r->SetCharManager(&cm);

	Player mb = Player(10, 10, "Master Black");
	cm.AddCharacter(&mb);

	bool render = true;;

	while (render) {
		//Processa eventos
		if (!ev.CheckEvents()) {
			render = false;
		}

		//Atualiza personagens


		//Os renderiza
		r->Render();


		al_rest(0.01);
	}

	delete r;
	return 0;
}
