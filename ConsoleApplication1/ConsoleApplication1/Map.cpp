#include "Map.hpp"

//Bitmap contendo todos os tiles
static Sprite* tile_files;

static ALLEGRO_BITMAP* cache_map = NULL;
static float lastsx = 0, lastsy = 0, lastw = 0, lasth = 0;

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

/***
	Desenha uma parte do mapa 
		startx - a posição x onde deve-se começar a desenhar o mapa, nas coords do jogo
		startx - posição y, nas coords do jogo
		width, height - tamanho, em pixels
		d = Display*/

ALLEGRO_BITMAP* Map::Render(float startx, float starty, float width, float height, ALLEGRO_DISPLAY* d) {

	if (startx == lastsx && starty == lastsy && width == lastw && height == lasth) {
		return cache_map;
	}

	if (cache_map)
		al_destroy_bitmap(cache_map);

	if (!tile_files || !tile_files->GetFrameImage())
		return NULL;



	cache_map = al_create_bitmap(width, height);

	al_set_target_bitmap(cache_map);

	int rx = 0;
	int ry = 0;

	for (int y = starty; y <= starty + (height / TILE_SIZE) + 1; y++) {
		for (int x = startx; x <= startx + (width / TILE_SIZE) + 1; x++) {
			if (x <= _width && y <= _height){
 				tile_files->SetFrame(_map_tile_indices[y*_width + x]);
				tile_files->NextFrame();
				al_draw_bitmap(tile_files->GetFrameImage(), rx, ry, 0);

				rx += TILE_SIZE;
			}
			else {
				goto next_row;
			}
		}
	next_row:

		ry += TILE_SIZE;
		rx = 0;
	}

	lastsx = startx;
	lastsy = starty;
	lastw = width;
	lasth = height;
	al_set_target_bitmap(al_get_backbuffer(d));

	return cache_map;


}


/* Carrega todos os tiles. Eles serão necessários para compor o mapa. */
void Map::LoadTiles() {
	tile_files = new Sprite("mapdata.png");

	if (!tile_files || !tile_files->GetFrameImage()){
		fprintf(stderr, "[Map] Não foi possível carregar o arquivo de tiles do mapa.\n");
		fprintf(stderr, "      Nenhum mapa poderá ser carregado corretamente. \n");
	}
}


