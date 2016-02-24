#include "Map.hpp"

//Bitmap contendo todos os tiles
static ALLEGRO_BITMAP* tile_files;

Map::Map(int w, int h) {
	_width = w;
	_height = h;
}

void Map::SetData(int* indices) {
	_map_tile_indices = indices;
}
int* Map::GetData() const{
	return _map_tile_indices;

}

/* Carrega todos os tiles. Eles serão necessários para compor o mapa. */
void Map::LoadTiles() {


}
