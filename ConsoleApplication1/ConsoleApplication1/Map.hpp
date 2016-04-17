#pragma once

/* Internal things for the map */
#include <allegro5/bitmap.h>
#include "Sprite.hpp"

#include <vector>

//Quantidade de pixels por unidade no jogo.
#define TILE_SIZE 32

struct CharacterData {
	unsigned int Type;
	unsigned int ID;
	unsigned int XPos;
	unsigned int YPos;
	unsigned int HP;	
	//unsigned int atk;
	//unsigned int def;
};


class Map {
private:
	int _width, _height;

	int _playerX, _playerY;

	/* Índices no array de tiles.*/
	int* _map_tile_indices;

	/* Dados dos chars no mapa */
	std::vector<CharacterData> _chardata;
public:
	Map(int w, int h);

	void SetData(int* indices);
	int* GetData() const;

	inline void SetInitialPlayerPos(int x, int y) {
		_playerX = x; _playerY = y;
	}

	inline void GetInitialPlayerPos(int& x, int& y) {
		x = _playerX; y = _playerY;
	}

	inline std::vector<CharacterData>* GetCharData() {
		return &_chardata;
	}

	inline void SetCharData(std::vector<CharacterData>* chardata) {
		_chardata = *chardata;
	}

	inline int GetWidth() { return _width; }
	inline int GetHeight() { return _height; }

	ALLEGRO_BITMAP* Render(float startx, float starty, float width, float height, ALLEGRO_DISPLAY* d);

	/* Load all map tiles */
	static void LoadTiles();
};