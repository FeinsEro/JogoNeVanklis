#pragma once
struct map
{
	struct layer *data;
	int total_layers;
};
struct layer
{
	int x, y; 
	struct tile *data;
	int w, h;
	int tile_spacing_w, tile_spacing_h;
};

struct tile
{
	BITMAP *pict;
	int flags;
	int trans;
};

#include <allegro5\allegro.h>
#include <allegro5\bitmap.h>
class TileMap {
private:
		//Bitmap contendo todos os tiles
		static ALLEGRO_BITMAP* tiles;	

		//Altura e largura padrão de cada tile, no arquivo.
		static int tile_width, tile_height; 

public:
	void Open(const char* path);
	

};