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

	Player mb = Player(10, 10, "Dann Von Veigar");
	Sprite s = Sprite("..\\characters\\abraoleos.bmp", 64, 64);
	mb.SetSprite(&s);

	cm.AddCharacter(&mb);

	bool render = true;;

	while (render) {
		//Processa eventos
		if (!ev.CheckEvents()) {
			render = false;
		}

		//Atualiza personagens
		Event e;
		if (ev.PopEvent(e)) {
			unsigned int x, y;
			mb.GetPosition(x, y);

			switch (e.keycode) {
			case ALLEGRO_KEY_UP:
				y--;
				break;

			case ALLEGRO_KEY_DOWN:
				y++;
				break;

			case ALLEGRO_KEY_LEFT:
				x--;
				break;

			case ALLEGRO_KEY_RIGHT:
				x++;
				break;



			}
			mb.SetPosition(x, y);

		}

		//Os renderiza
		r->Render();


		al_rest(0.01);
	}

	delete r;
	return 0;
}
