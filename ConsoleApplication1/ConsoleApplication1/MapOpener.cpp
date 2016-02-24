#include "MapOpener.hpp"

Map* MapOpener::Open(std::string path) {
	FILE* fMap;
	if (fopen_s(&fMap, path.c_str(), "rb") != 0) {
		return NULL; //Erro ao abrir o arquivo.
	}

	MapFile mapData;
	fread(&mapData, sizeof(MapFile), 1, fMap);

	if (mapData.width == 0 || mapData.height == 0)
		return NULL; //O conteúdo do mapa não pode ser zero

	if (mapData.signature[0] != 'W' && mapData.signature[1] != 'E' &&
		mapData.signature[2] != 'R' && mapData.signature[3] != 'L') {
		return NULL; //Magic number do arquivo errado
	}

	if (mapData.offset_to_data < sizeof(MapFile)) {
		return NULL; //O offset para os dados aponta para o próprio header.
	}

	Map* mp = new Map(mapData.width, mapData.height);

	int* data = new int[mapData.width, mapData.height];
	fseek(fMap, mapData.offset_to_data, 0);

	if (fread(data, sizeof(int), mapData.width * mapData.height, fMap) !=
		mapData.width * mapData.height) {
		//Não leu tudo.
		delete data;
		return NULL;
	}

	mp->SetData(data);
	return mp;

}