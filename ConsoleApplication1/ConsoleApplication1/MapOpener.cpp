#include "MapOpener.hpp"

Map* MapOpener::Open(std::string path) {
	FILE* fMap;
	int err = fopen_s(&fMap, path.c_str(), "rb");
	if (err != 0) {
		fprintf(stderr, "[MapOpener] Erro %d ao abrir o mapa %s\n", err, path.c_str());
		return NULL; //Erro ao abrir o arquivo.
	}

	MapFile mapData;
	fread(&mapData, sizeof(MapFile), 1, fMap);

	if (mapData.width == 0 || mapData.height == 0)
		return NULL; //O conte�do do mapa n�o pode ser zero

	if (mapData.signature[0] != 'W' && mapData.signature[1] != 'E' &&
		mapData.signature[2] != 'R' && mapData.signature[3] != 'L') {
		return NULL; //Magic number do arquivo est� errado
	}

	if (mapData.offset_to_data < sizeof(MapFile)) {
		return NULL; //O offset para os dados aponta para o pr�prio header.
	}

	Map* mp = new Map(mapData.width, mapData.height);

	int* data = new int[mapData.width * mapData.height];
	fseek(fMap, mapData.offset_to_data, 0);

	if (fread(data, sizeof(int), mapData.width * mapData.height, fMap) !=
		mapData.width * mapData.height) {
		//N�o leu tudo.
		delete data;
		return NULL;
	}

	fprintf(stderr, "[MapOpener] O mapa %s possui %d x %d blocos\n",
		path.c_str(), mapData.width, mapData.height);
	fprintf(stderr, "	Posi��o inicial do player: (%d,%d)\n",
		mapData.playerX, mapData.playerY);

	mp->SetData(data);
	mp->SetInitialPlayerPos(mapData.playerX, mapData.playerY);
	return mp;

}