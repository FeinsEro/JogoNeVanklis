#pragma once

/* Internal things for the map */
#include <allegro5/bitmap.h>

class Map {
private:
	int _width, _height;

	/* Índices no array de tiles.*/
	int* _map_tile_indices;

public:
	Map(int w, int h);

	void SetData(int* indices);
	int* GetData() const;

	/* Load all map tiles */
	static void LoadTiles();
};