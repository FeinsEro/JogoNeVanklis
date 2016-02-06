#include "Sprite.hpp"

Sprite::Sprite(){
	
}

Sprite::Sprite(const char* path, int frame_width, int frame_height){
	this->sheet_path = std::string(path);
	this->_frame_width = frame_width;
	this->_frame_height = frame_height;
	UpdateSheet();

}

void Sprite::GetPath(std::string& val) { val = this->sheet_path; }
void Sprite::SetPath(std::string val) { this->sheet_path = val; UpdateSheet(); }


void Sprite::UpdateSheet() {
	_sheet_cache = al_load_bitmap(this->sheet_path.c_str());

	this->_image_height = al_get_bitmap_height(_sheet_cache);
	this->_image_width = al_get_bitmap_width(_sheet_cache);

	this->_frame_count = (_image_width / _frame_width) * (_image_height / _frame_height);

}
ALLEGRO_BITMAP* Sprite::NextFrame(){
	
}
ALLEGRO_BITMAP* Sprite::PreviousFrame(){}
ALLEGRO_BITMAP* Sprite::StepFrames(int){}

int Sprite::GetFrameNumber(){}
ALLEGRO_BITMAP* Sprite::GetFrameImage(){}