#include <stdio.h>

//Includes do Allegro

#include "CharacterManager.hpp"
#include "EventQueue.hpp"
#include "Renderer.hpp"
#include "MapOpener.hpp"

#include "CharFactory.hpp"
#include "Tree.hpp"

#include <iostream>
#include <sstream> //stringstream

#include <allegro5/allegro_windows.h>

bool cima = false, baixo = false, direita = false, esquerda = false;
int frames = 0;
int main(int argc, char **argv) {

	Renderer* r = NULL;
	try {
		r = new Renderer(800, 600);
	
		EventQueue ev(r);
	
		CharacterManager cm;
		r->SetCharManager(&cm);

		Player mb = Player(10, 10, "Dann Von Veigar");
	

		Item it = Item("Insígnia do MC Bin Laden", "insignia do mestre Bin Laden", 3000);
		mb.AddItem(&it);

		Sprite s = Sprite("..\\characters\\Normal.png", 1.5f);
		mb.SetSprite(&s);

		CharFactory* cf = new CharFactory(&cm);

		Tree t = Tree(20, 20);
		Sprite stree = Sprite("..\\characters\\arvore1.png", 60, 80);
		t.SetSprite(&stree);

		cf->RegisterCharacter(t.GetTypeID(), &t);


		cm.AddCharacter(&mb);
		cm.SetPlayer(&mb);

		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 15, 15));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 50, 15));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 95, 15));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 15, 50));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 50, 50));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 95, 50));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 15, 95));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 50, 95));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 95, 95));

		Map* m;
		

		MapOpener mpop;
		m = mpop.Open("..\\maps\\map1.map");
		
		if (!m) {
			char strmaperr[32];
			sprintf_s(strmaperr, 32, "Erro ao abrir o mapa!");
			throw std::runtime_error(strmaperr);
		}


		HUD* hud = new HUD(&mb);
		r->SetHUD(hud);

	

		bool render = true;;
		int playerdx = 0, playerdy = 0;

		while (render) {
			
			//Atualiza personagens


			//Processa eventos
			if (!ev.CheckEvents()) {
				render = false;
			}

			
			Event e;

			if (ev.PopEvent(e)) {
				unsigned int x, y;
				mb.GetPosition(x, y);

				int dx = 0, dy = 0;

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

				if (cima) dy--;
				if (baixo) dy++;
				if (direita) dx++;
				if (esquerda) dx--;

				

				x += dx;
				y += dy;

				playerdx += dx;
				playerdy += dy;

				x = max(1, x);
				y = max(1, y);

				mb.SetPosition(x, y);

			}


			if (frames % 16 == 0) {
				mb.Andar(playerdx, playerdy);
				playerdx = 0;
				playerdy = 0;
			}

			cm.DoAllEvents();
			
			//Os renderiza
			r->Render();

			frames++;
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
