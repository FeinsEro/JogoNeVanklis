#pragma once

/*	Map opener class
	Opens a map, returns a Map object */

#include <string>

#include "Map.hpp"

/* O mapa � um arquivo bin�rio. Sua estrutura � definida como o campo abaixo */
struct MapFile {
	char signature[4];		//Assinatura do arquivo = "WERL"
	int width;			//Largura
	int height;			//Altura
	int offset_to_data;	//Posi��o do arquivo onde est�o os dados do mapa.
};

class MapOpener {
private:
	std::string _path;
	
	unsigned int _width, _height;

public:
	/* Opens a file. Returns a Map on success, false on error*/
	Map* Open(std::string path);

	
};