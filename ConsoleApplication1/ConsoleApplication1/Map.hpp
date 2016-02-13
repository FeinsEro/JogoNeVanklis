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
	int tile_index;
	int flags;
	int trans;
};

#include <allegro5\allegro.h>
#include <allegro5\bitmap.h>

#include <stdexcept> //std::runtime_error()

class TileMap {
private:
		
		std::string map_path; //Caminho do mapa
		map map_file;

public:
	TileMap();

	void Open(const char* path);
	

};