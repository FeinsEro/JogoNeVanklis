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

#include "Asura.hpp"
#include "Akhbran.hpp"
/* 
	EU
	TU
	N�S BOTA NELA
	O DANN CHEGOU
	� O PREDADOR DE PERERECA
	
*/

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

		Item it = Item("Ins�gnia do MC Bin Laden", "insignia do mestre Bin Laden", 3000);
		player.AddItem(&it);

		Sprite s = Sprite("..\\characters\\dann.png", 1.5f, 0);
		player.SetSprite(&s);

		Asura asu = Asura{ 0,0 };
		Akhbran ahk = Akhbran{ 0,0 };

		CharFactory* cf = new CharFactory(&cm);

		Tree t = Tree(20, 20);
		Sprite stree = Sprite("..\\characters\\arvore1.png", 1, 60, 80);
		t.SetSprite(&stree);

		cf->RegisterCharacter(t.GetTypeID(), &t);


		cm.AddCharacter(&player);
		cm.SetPlayer(&player);

		
		/*
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 3, 8));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 6, 11));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 9, 20));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 12, 25));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 15, 20));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 18, 11));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 21, 8));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 24, 11));
		cm.AddCharacter(cf->PutCharacter(t.GetTypeID(), 27, 20));
		*/

		cm.AddCharacter(&asu);
		cm.AddCharacter(&ahk);

		Map* m;
		Map::LoadTiles();

		MapOpener mpop;
		m = mpop.Open("..\\maps\\map2.map");		

		if (!m) {
			char strmaperr[32];
			sprintf_s(strmaperr, 32, "Erro ao abrir o mapa!");
			throw std::runtime_error(strmaperr);
		}


		int px, py;
		m->GetInitialPlayerPos(px, py);

		float fx = px, fy = py;
		player.SetPosition(fx, fy);


		std::vector<CharacterData>* chd = m->GetCharData();

		if (chd->size() > 0) {
			for (auto i = chd->begin(); i != chd->end(); i++) {
				cm.AddCharacter(cf->PutCharacter(i->Type, i->XPos, i->YPos));
			}

		}

		r->SetMap(m);
		cm.SetMap(m);

		HUD* hud = new HUD(&player);
		r->SetHUD(hud);

	

		bool render = true;

		double fps = (1/60), start_time, end_time;

		float start_animations = al_get_time();
		float start_events = al_get_time();

		float playerdx = 0, playerdy = 0;

		start_time = al_get_time();

		while (render) {
			
			//Run events in 15fps.
			float end_events = al_get_time();
			if ((end_events - start_events) >= 1/15.0f){
				cm.DoAllEvents();
				start_events - end_events;
			}

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

					//Enumera os itens no invent�rio do player.
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

					MessageBoxA(al_get_win_window_handle(r->GetDisplay()), line.str().c_str(), "Invent�rio", 0);

					break;


				}

				
			}

			float end_animations = al_get_time();
			/* Run animations in 5 fps by default. */
			if ((end_animations - start_animations) >= 1/5.0f) {
				player.Andar(playerdx, playerdy);
				asu.Andar(playerdx, playerdy);
				ahk.Andar(playerdx, playerdy);
				playerdx = 0;
				playerdy = 0;
				start_animations = end_animations;

			}

			cm.DoAllEvents();
			
			//Os renderiza
			r->Render();


			end_time = al_get_time();

			if ((end_time - start_time) < fps) {
				double delta = (end_time - start_time);
				Sleep((fps - delta) * 1000);
				
			}
			//printf("\r%.5f ms", end_time - start_time);
			
			start_time = al_get_time();

			frames++;
		}


	}
	catch (std::runtime_error& e) {
		if (r)
			MessageBoxA(r->GetDisplay() ? al_get_win_window_handle(r->GetDisplay()) : NULL,
				e.what(), "Dois Dem�nios - Erro", MB_ICONERROR);
		else
			MessageBoxA(NULL, e.what(), "Dois Dem�nios - Erro", MB_ICONERROR);
		return -1;
	}

	delete r;
	return 0;
}
