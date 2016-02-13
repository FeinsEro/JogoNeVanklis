#include "Map.hpp"

//Bitmap contendo todos os tiles
static ALLEGRO_BITMAP* tiles;

//Altura e largura padrão de cada tile.
const int tile_width = 48, tile_height = 48;

const char* tile_file_path = "tiles.bmp";

TileMap::TileMap() {
	if (!tiles) {
		tiles = al_load_bitmap(tile_file_path);

		if (!tiles) {
			throw std::runtime_error("Arquivo de tiles não encontrado. ");
		}
	}

}

void TileMap::Open(const char* path) {

}