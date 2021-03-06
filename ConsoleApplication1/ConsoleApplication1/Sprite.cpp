#include "Sprite.hpp"

Sprite::Sprite(){
	
}

Sprite::Sprite(const char* path, int zindex, int frame_width, int frame_height) {
	this->sheet_path = std::string(path);
	this->_frame_width = frame_width;
	this->_frame_height = frame_height;
	this->_frame_cache = NULL;

	this->_zoom = 1.0f;
	this->_zIndex = zindex;

	UpdateSheet();

}

Sprite::Sprite(const char* path, float zoomfactor, int zindex, int frame_width, int frame_height) {
	this->sheet_path = std::string(path);
	this->_frame_width = frame_width;
	this->_frame_height = frame_height;
	this->_frame_cache = NULL;

	this->_zoom = zoomfactor;
	this->_zIndex = zindex;

	UpdateSheet();

}

void Sprite::GetPath(std::string& val) { val = this->sheet_path; }
void Sprite::SetPath(std::string val) { this->sheet_path = val; UpdateSheet(); }

void Sprite::SetZoomFactor(float zoom) { _zoom = zoom; }
float Sprite::GetZoomFactor() { return _zoom; }

void Sprite::UpdateSheet() {
	_sheet_cache = al_load_bitmap(this->sheet_path.c_str());

	if (!_sheet_cache)
		return;

	this->_image_height = al_get_bitmap_height(_sheet_cache);
	this->_image_width = al_get_bitmap_width(_sheet_cache);

	//Depois mudar a transparência pra uma cor menos usada (como o tradicional magenta)
	al_convert_mask_to_alpha(_sheet_cache, al_map_rgb(255, 0, 255));

	this->_frame_count = (_image_width / _frame_width) * (_image_height / _frame_height);

	this->_frame_num = 0;
	this->_frame_x = 0;
	this->_frame_y = 0;

	fprintf(stderr, "[Sprite] Spritesheet adicionado: %s\n", this->sheet_path.c_str());
	fprintf(stderr, "[Sprite] \tTamanho: %dx%d\n", _image_width, _image_height);
	fprintf(stderr, "[Sprite] \t%d frames detectados\n", _frame_count);

	this->StepFrames(0); //carrega o primeiro frame
}
ALLEGRO_BITMAP* Sprite::NextFrame(bool returnImage){
	return this->StepFrames(1, returnImage);	
}
ALLEGRO_BITMAP* Sprite::PreviousFrame(bool returnImage){
	return this->StepFrames(-1, returnImage);
}
ALLEGRO_BITMAP* Sprite::StepFrames(int num, bool returnImage) {
	
	this->_frame_num += num;
	
	if (this->_frame_num < 0) {
		this->_frame_num = this->_frame_count - 1;
	}

	if (this->_frame_num >= this->_frame_count) {
		this->_frame_num = 0;
	}


	if (!returnImage){
		al_destroy_bitmap(this->_frame_cache);
		this->_frame_cache = NULL;
		return NULL; //Pula os cálculos de corte do frame.
	}

	this->_frame_y = (this->_frame_num * _frame_width) / _image_width;
	this->_frame_x = (this->_frame_num * _frame_width) % _image_width;
	
	//Talvez usar unique_ptr no bitmap do frame
	this->_frame_cache = al_create_sub_bitmap(this->_sheet_cache, this->_frame_x, this->_frame_y,
		this->_frame_width, this->_frame_height);

	

	return this->_frame_cache;
}

int Sprite::GetFrameNumber() {
	return this->_frame_num;
}

ALLEGRO_BITMAP* Sprite::GetFrameImage() {
	if (!this->_frame_cache) {
		this->StepFrames(0);
	}
	return this->_frame_cache;
}

void Sprite::SetFrame(int num) {
	this->_frame_num = num;
}