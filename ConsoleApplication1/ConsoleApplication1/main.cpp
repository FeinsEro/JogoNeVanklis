#include <stdio.h>

//Includes do Allegro

#include "CharacterManager.hpp"
#include "EventQueue.hpp"
#include "Renderer.hpp"

#include <iostream>
#include <sstream> //stringstream

#include <allegro5/allegro_windows.h>

bool cima = false, baixo = false, direita = false, esquerda = false;
int main(int argc, char **argv) {

	Renderer* r = NULL;
	try {
		r = new Renderer(640, 480);
	
		EventQueue ev(r);
	
		CharacterManager cm;
		r->SetCharManager(&cm);

		Player mb = Player(10, 10, "Dann Von Veigar");

		Item it = Item("Insígnia do MC Bin Laden", "insignia do mestre Bin Laden", 3000);
		mb.AddItem(&it);

		Sprite s = Sprite("..\\characters\\abraoleos.bmp", 64, 64);
		mb.SetSprite(&s);

		cm.AddCharacter(&mb);

		HUD* hud = new HUD(&mb);
		r->SetHUD(hud);

	

		bool render = true;;

		while (render) {
			//Processa eventos
			if (!ev.CheckEvents()) {
				render = false;
			}

			//Atualiza personagens
			Event e;
			while (ev.PopEvent(e)) {
				unsigned int x, y;
				mb.GetPosition(x, y);

			


				switch (e.keycode) {
				case ALLEGRO_KEY_UP:
					if (e.key_status == ButtonStatus::Pressed)
						cima = true;
					else if (e.key_status == ButtonStatus::Released)
						cima = false;
					break;

				case ALLEGRO_KEY_DOWN:
					if (e.key_status == ButtonStatus::Pressed)
						baixo = true;
					else if (e.key_status == ButtonStatus::Released)
						baixo = false;
					break;

				case ALLEGRO_KEY_LEFT:
					if (e.key_status == ButtonStatus::Pressed)
						esquerda = true;
					else if (e.key_status == ButtonStatus::Released)
						esquerda = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					if (e.key_status == ButtonStatus::Pressed)
						direita = true;
					else if (e.key_status == ButtonStatus::Released)
						direita = false;
					break;

				case ALLEGRO_KEY_I:

					if (e.keyletter != 'i') continue;

					//Enumera os itens no inventário do player.
					std::vector<Item*>* list;
					mb.GetAllItems(&list);

					std::stringstream line;

					for (auto i = list->begin();
					i != list->end();
						i++) {
						std::string name;
						(*i)->GetName(name);
						line << (*i)->GetID() << " - " << name << " - " << (*i)->GetValue() << " money" << std::endl;
					
					}

					MessageBoxA(al_get_win_window_handle(r->GetDisplay()), line.str().c_str(), "Inventário", 0);

					break;


				}

				if (cima) y--;
				if (baixo) y++;
				if (direita) x++;
				if (esquerda) x--;

				mb.SetPosition(x, y);

			}

			//Os renderiza
			r->Render();


			al_rest(0.01);
		}

	}
	catch (std::runtime_error& e) {
		if (r)
			MessageBoxA(r->GetDisplay() ? al_get_win_window_handle(r->GetDisplay()) : NULL,
				e.what(), "Um erro ocorreu", MB_ICONERROR);
		else
			MessageBoxA(NULL, e.what(), "Um erro ocorreu", MB_ICONERROR);
		return -1;
	}

	delete r;
	return 0;
}
