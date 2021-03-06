#pragma once

/*	Sprite
	Controla todos os sprites do jogo. 
	
	Um sprite �, basicamente, uma imagem 2d m�vel no jogo e anim�vel.
	N�o vamos cuidar do movimento, apenas da anima��o. */

#include <string>
#include <algorithm> //max()

#include <allegro5/allegro.h>

#define DEFAULT_FRAME_WIDTH 32
#define DEFAULT_FRAME_HEIGHT 32 

class Sprite {
	
private:

	int _image_width, _image_height; //Largura e altura da imagem inteira (em pixels)
	int _frame_width, _frame_height; //Largura e altura do frame (em pixels)
	int _frame_count; //Frames da imagem

	float _zoom; //Zoom factor, default is 1.

	int _frame_x, _frame_y; //X e Y do frame atual
	int _frame_num; //O n�mero do frame atual

	std::string sheet_path; //O caminho da spritesheet
	ALLEGRO_BITMAP* _sheet_cache; 

	ALLEGRO_BITMAP* _frame_cache; //Cache do frame atual

	void UpdateSheet(); 

	//O zindex do sprite. Quanto maior esse n�mero, mais 'na frente' ele vai ser renderizado.
	int _zIndex;

public:
	Sprite();
	Sprite(const char* path, int zindex = 1,
		int frame_width = DEFAULT_FRAME_WIDTH, int height = DEFAULT_FRAME_HEIGHT);
	Sprite(const char* path, float zoomfactor, int zindex = 1,
		int frame_width = DEFAULT_FRAME_WIDTH, int height = DEFAULT_FRAME_HEIGHT);
	
	void GetPath(std::string&);
	void SetPath(std::string);

	void SetZoomFactor(float);
	float GetZoomFactor();

	/*	As fun��es abaixo modificam o frame atual. Se returnImage for falso, ele
		vai retornar NULL e n�o retorna imagem nenhuma 
		Isso pode economizar mem�ria em situa��es onde voc� s� quer modificar 
		o frame atual, sem retorno de imagem. 

		StepFrames(n, false) N�O � igual a SetFrame(n)
		SetFrames() n�o checa os limites de frame do sprite.
	*/

	ALLEGRO_BITMAP* NextFrame(bool returnImage = true);
	ALLEGRO_BITMAP* PreviousFrame(bool returnImage = true);
	ALLEGRO_BITMAP* StepFrames(int, bool returnImage = true);

	int GetFrameNumber();
	ALLEGRO_BITMAP* GetFrameImage();
	void SetFrame(int);

	inline int GetZIndex() { return _zIndex; }
	inline void SetZIndex(int i) { _zIndex = i; }

	inline int GetFrameWidth() { return _frame_width; }
	inline int GetFrameHeight() { return _frame_height; }

};

