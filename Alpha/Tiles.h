#ifndef _TILES_H_
#define _TILES_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>

const int	TILE_WIDTH = 32, TILE_HEIGHT = 32,		//in pixels
			MAP_WIDTH = 50, MAP_HEIGHT = 50,		//in chunks
			IS_WALL = 47,							//threshold to be a wall
			DEATH_LIMIT = 3,						
			BIRTH_LIMIT = 4,
			STEPS = 6;

class texture;
class tile;
class spritesheet;
class map;
class player;

class texture{
public:
	texture(SDL_Renderer* renderer = NULL, std::string path = "");
	~texture();
	void show(int x, int y, SDL_Renderer* renderer = NULL, SDL_Rect* src = NULL);
	int width, height;
	SDL_Texture* image;
};

class tile{
public:
	tile();
	~tile();
	tile	*next_tile_x, 
			*next_tile_y, 
			*prev_tile_x, 
			*prev_tile_y;
	int tile_ID;
	int width = TILE_WIDTH, height = TILE_HEIGHT;
	SDL_Rect clip_box;
};

class spritesheet{
public:
	spritesheet(texture* incoming);
	~spritesheet();
	void generate();
	void draw(int tileID, int x, int y, SDL_Renderer* renderer, SDL_Rect& camera);
private:
	texture *sheet;
	int total_tiles;
	tile *root = NULL, *walker = NULL;
};

class map{
public:
	map();
	~map();
	void initialize();
	void to_file();
	int check_neighbors(int, int);
	int get_value(int, int);
	void simulate();
private:
	int data[MAP_WIDTH][MAP_HEIGHT];
	std::ofstream textfile;
};

class player{
public:
	player();
	~player();
	void load_sheet(std::string path = "");
	void center_camera(SDL_Rect& camera);
	void handle_event(SDL_Event& e);
	void move();
	void render(int camera_x, int camera_y);
	int get_pos_x();
	int get_pos_y();
private:
	spritesheet* sheet = NULL;
	int x, y;
	int speed_x, speed_y;
};

#endif