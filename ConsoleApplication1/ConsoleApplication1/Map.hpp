#pragma once

/* Internal things for the map */
#include <allegro5/bitmap.h>
#include "Sprite.hpp"

//Quantidade de pixels por unidade no jogo.
#define TILE_SIZE 32

class Map {
private:
	int _width, _height;

	int _playerX, _playerY;

	/* Índices no array de tiles.*/
	int* _map_tile_indices;

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


	inline int GetWidth() { return _width; }
	inline int GetHeight() { return _height; }

	ALLEGRO_BITMAP* Render(float startx, float starty, float width, float height, ALLEGRO_DISPLAY* d);

	/* Load all map tiles */
	static void LoadTiles();
};