#pragma once

/*	Sprite
	Controla todos os sprites do jogo. 
	
	Um sprite é, basicamente, uma imagem 2d móvel no jogo e animável.
	Não vamos cuidar do movimento, apenas da animação. */

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
	int _frame_num; //O número do frame atual

	std::string sheet_path; //O caminho da spritesheet
	ALLEGRO_BITMAP* _sheet_cache; 

	ALLEGRO_BITMAP* _frame_cache; //Cache do frame atual

	void UpdateSheet(); 

public:
	Sprite();
	Sprite(const char* path,
		int frame_width = DEFAULT_FRAME_WIDTH, int height = DEFAULT_FRAME_HEIGHT);
	Sprite(const char* path, float zoomfactor,
		int frame_width = DEFAULT_FRAME_WIDTH, int height = DEFAULT_FRAME_HEIGHT);
	
	void GetPath(std::string&);
	void SetPath(std::string);

	void SetZoomFactor(float);
	float GetZoomFactor();

	ALLEGRO_BITMAP* NextFrame();
	ALLEGRO_BITMAP* PreviousFrame();
	ALLEGRO_BITMAP* StepFrames(int);

	int GetFrameNumber();
	ALLEGRO_BITMAP* GetFrameImage();
	void SetFrame(int);

};

