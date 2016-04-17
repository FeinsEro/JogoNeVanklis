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
		return NULL; //O conteúdo do mapa não pode ser zero

	if (mapData.signature[0] != 'W' && mapData.signature[1] != 'E' &&
		mapData.signature[2] != 'R' && mapData.signature[3] != 'L') {
		return NULL; //Magic number do arquivo está errado
	}

	if (mapData.offset_to_data < sizeof(MapFile)) {
		return NULL; //O offset para os dados aponta para o próprio header.
	}

	Map* mp = new Map(mapData.width, mapData.height);

	int* data = new int[mapData.width * mapData.height];
	fseek(fMap, mapData.offset_to_data, 0);

	if (fread(data, sizeof(int), mapData.width * mapData.height, fMap) !=
		mapData.width * mapData.height) {
		//Não leu tudo.
		delete data;
		return NULL;
	}

	fprintf(stderr, "[MapOpener] O mapa %s possui %d x %d blocos\n",
		path.c_str(), mapData.width, mapData.height);
	fprintf(stderr, "	Posição inicial do player: (%d,%d)\n",
		mapData.playerX, mapData.playerY);

	mp->SetData(data);
	mp->SetInitialPlayerPos(mapData.playerX, mapData.playerY);


	if (mapData.offset_to_chars == 0) {
		fprintf(stderr, "AVISO: Não há objetos no mapa.\n");
	} else {
		fseek(fMap, mapData.offset_to_chars, 0);
		/* O primeiro campo é a quantidade de objetos a serem carregados*/
		uint32_t objCount = 0;
		fread(&objCount, sizeof(uint32_t), 1, fMap);
		fprintf(stderr, "O mapa possui %d objetos\n", objCount);

		auto mapobjects = std::vector<CharacterData>();

		for (int i = 0; i < objCount; i++) {
			/* Para cada campo de objetos há o seu tamanho.*/
			int size;
			fread(&size, sizeof(int), 1, fMap);

			/* Escolhe o menor dos tamanhos */
			size = min(sizeof(CharacterData), size);

			/* O restante tem o layout igual ao do campo CharacterData*/
			CharacterData chdata;
			fread(&chdata, size, 1, fMap);
			
			mapobjects.push_back(chdata);
		}

		mp->SetCharData(&mapobjects);
	}

	
	fclose(fMap);
	return mp;

}