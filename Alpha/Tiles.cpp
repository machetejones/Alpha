#include <Tiles.h>

texture::texture(SDL_Renderer* renderer, std::string path){
	if (renderer != NULL && path != ""){
		image = IMG_LoadTexture(renderer, path.c_str());
		SDL_QueryTexture(image, NULL, NULL, &width, &height);
	}
	else{
		//not sure where I'm going with this part yet, probably has to do with creating textures dynamically.
	}
}
texture::~texture(){
	if (image != NULL){
		SDL_DestroyTexture(image);
	}
}
void texture::show(int x, int y, SDL_Renderer* renderer, SDL_Rect* src){
	SDL_Rect dst = { x, y, width, height };
	if (src != NULL){
		dst.w = src->w;
		dst.h = src->h;
	}
	SDL_RenderCopy(renderer, image, src, &dst);
}

tile::tile(){
	tile_ID = 0;
	clip_box = { 0, 0, 0, 0 };
	next_tile_x = NULL; next_tile_y = NULL;
	prev_tile_x = NULL; prev_tile_y = NULL;
}
tile::~tile(){

}

spritesheet::spritesheet(texture* incoming){
	total_tiles = 0;
	sheet = incoming;
	generate();
}
spritesheet::~spritesheet(){
	sheet = NULL;
}
void spritesheet::generate()
{
	root = new tile;
	walker = root;
	total_tiles = (sheet->width / root->width);

	for (int i = 0; i < total_tiles; i++)
	{
		walker->tile_ID = i;
		walker->clip_box.x = walker->width * i;
		walker->clip_box.y = 0;
		walker->clip_box.w = walker->width;
		walker->clip_box.h = walker->height;
		walker->next_tile_x = new tile;
		walker->next_tile_x->prev_tile_x = walker;
		walker = walker->next_tile_x;
	}
}
void spritesheet::draw(int tileID, int x, int y, SDL_Renderer* renderer, SDL_Rect& camera){
	walker = root;
	while (walker->tile_ID != tileID){
		walker = walker->next_tile_x;
	}
	sheet->show(x, y, renderer, &walker->clip_box);
}

map::map(){

}
map::~map(){

}
void map::initialize(){
	srand((unsigned int)time(NULL));
	for (int y = 0; y < MAP_HEIGHT; y++){
		for (int x = 0; x < MAP_WIDTH; x++){
			if (rand() % 100 < IS_WALL){
				data[x][y] = 1;
			}
			else{
				data[x][y] = 0;
			}
		}
	}
}
int map::get_value(int x, int y){
	return data[x][y];
}

int map::check_neighbors(int x, int y){
	int count = 0;
	for (int i = -1; i < 2; i++){
		for (int j = -1; j < 2; j++){
			int neighborX = x + j;
			int neighborY = y + i;
			if (i == 0 && j == 0){
			}
			else if (neighborX < 0 || neighborY < 0 || neighborX >= MAP_WIDTH || neighborY >= MAP_HEIGHT){
				count++;
			}
			else if (data[neighborX][neighborY] == 1){
				count++;
			}
		}
	}
	return count;
}
void map::simulate(){
	for (int s = 0; s < STEPS; s++){
		int temp_data[MAP_WIDTH][MAP_HEIGHT];
		for (int y = 0; y < MAP_HEIGHT; y++){
			for (int x = 0; x < MAP_WIDTH; x++){
				int neighbors = check_neighbors(x, y);
				if (data[x][y] == 1){
					if (neighbors < DEATH_LIMIT){
						temp_data[x][y] = 0;
					}
					else{
						temp_data[x][y] = 1;
					}
				}
				else{
					if (neighbors > BIRTH_LIMIT){
						temp_data[x][y] = 1;
					}
					else{
						temp_data[x][y] = 0;
					}
				}
			}
		}
		for (int y = 0; y < MAP_HEIGHT; y++){
			for (int x = 0; x < MAP_WIDTH; x++){
				data[x][y] = temp_data[x][y];
			}
		}
	}
}
void map::to_file(){
	std::ofstream textfile;
	textfile.open("map.txt");
	for (int y = 0; y < MAP_HEIGHT; y++){
		for (int x = 0; x < MAP_WIDTH; x++){
			textfile << data[x][y];
		}
		textfile << std::endl;
	}
}

player::player(){

}
player::~player(){

}
void player::load_sheet(std::string path){

}
void player::center_camera(SDL_Rect& camera){

}
void player::handle_event(SDL_Event& e){

}

void player::move(){
	x += speed_x;
	y += speed_y;
}

void player::render(int camera_x, int camera_y){

}

int player::get_pos_x(){
	return x;
}
int player::get_pos_y(){
	return y;
}
