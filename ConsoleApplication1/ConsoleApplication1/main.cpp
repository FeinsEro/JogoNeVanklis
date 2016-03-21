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

int frames = 0;
int main(int argc, char **argv) {

	Renderer* r = NULL;
	try {
		r = new Renderer(800, 600);
	
		EventQueue ev(r);
	
		CharacterManager cm;
		r->SetCharManager(&cm);

		Player player = Player(10, 10, "Dann Von Veigar");
		player.SetEventQueue(&ev);

		Item it = Item("Insígnia do MC Bin Laden", "insignia do mestre Bin Laden", 3000);
		player.AddItem(&it);

		Sprite s = Sprite("..\\characters\\Normal.png", 1.5f);
		player.SetSprite(&s);

		CharFactory* cf = new CharFactory(&cm);

		Tree t = Tree(20, 20);
		Sprite stree = Sprite("..\\characters\\arvore1.png", 60, 80);
		t.SetSprite(&stree);

		cf->RegisterCharacter(t.GetTypeID(), &t);


		cm.AddCharacter(&player);
		cm.SetPlayer(&player);

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
		player.SetPosition(fx, fy);
		

		if (!m) {
			char strmaperr[32];
			sprintf_s(strmaperr, 32, "Erro ao abrir o mapa!");
			throw std::runtime_error(strmaperr);
		}


		r->SetMap(m);
		cm.SetMap(m);

		HUD* hud = new HUD(&player);
		r->SetHUD(hud);

	

		bool render = true;

		double fps = (1/60), start_time, end_time;

		float playerdx = 0, playerdy = 0;

		start_time = al_get_time();

		while (render) {
			
			//Atualiza personagens
			cm.DoAllEvents();

			//Processa eventos
			if (!ev.CheckEvents()) {
				render = false;
			}


			player.Control(m);
			Event e;

			if (ev.PopEvent(e)) {

				switch (e.keycode) {

				case ALLEGRO_KEY_I:

					if (e.keyletter != 'i') continue;

					//Enumera os itens no inventário do player.
					std::vector<Item*>* list;
					player.GetAllItems(&list);

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

				
			}


			if (frames % 12 == 0) {
				player.Andar(playerdx, playerdy);
				playerdx = 0;
				playerdy = 0;

			}

			cm.DoAllEvents();
			
			//Os renderiza
			r->Render();


			end_time = al_get_time();

			if ((end_time - start_time) < fps) {
				double delta = (end_time - start_time);
				Sleep((fps - delta) * 1000);
				
			}
			
			start_time = al_get_time();

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
