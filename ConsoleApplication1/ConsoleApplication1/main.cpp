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

		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 3, 8));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 6, 11));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 9, 20));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 12, 25));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 15, 20));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 18, 11));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 21, 8));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 24, 11));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 27, 20));

		Map* m;
		Map::LoadTiles();

		MapOpener mpop;
		m = mpop.Open("..\\maps\\map2.map");

		int px, py;
		m->GetInitialPlayerPos(px, py);

		float fx = px, fy = py;
		mb.SetPosition(fx, fy);
		

		if (!m) {
			char strmaperr[32];
			sprintf_s(strmaperr, 32, "Erro ao abrir o mapa!");
			throw std::runtime_error(strmaperr);
		}


		r->SetMap(m);

		HUD* hud = new HUD(&mb);
		r->SetHUD(hud);

	

		bool render = true;;
		float playerdx = 0, playerdy = 0;

		while (render) {
			
			//Atualiza personagens


			//Processa eventos
			if (!ev.CheckEvents()) {
				render = false;
			}

			
			Event e;

			if (ev.PopEvent(e)) {
				float x, y;
				mb.GetPosition(x, y);

				float dx = 0, dy = 0;

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

				if (cima) dy -= .1;
				if (baixo) dy += .1;
				if (direita) dx += .1;
				if (esquerda) dx -= .1;

				

				x += dx;
				y += dy;

				playerdx += dx;
				playerdy += dy;

				x = max(1, x);
				y = max(1, y);

				x = min(x, m->GetWidth());
				y = min(y, m->GetHeight());

				mb.SetPosition(x, y);

			}


			if (frames % 8 == 0) {
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
				e.what(), "Dois Demônios - Erro", MB_ICONERROR);
		else
			MessageBoxA(NULL, e.what(), "Dois Demônios - Erro", MB_ICONERROR);
		return -1;
	}

	delete r;
	return 0;
}
