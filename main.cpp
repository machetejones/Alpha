#include <Tiles.h>

const int	SCREEN_WIDTH = 800,
SCREEN_HEIGHT = 600;

SDL_Window* window;
SDL_Renderer* renderer;

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Alpha", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}
void close()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

int main(int argc, char* args[])
{
	init();
	SDL_Event e;
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//map newmap;
	//newmap.initialize();
	//newmap.simulate();
	//newmap.to_file();

	//texture* tileset = new texture(renderer, "Images/tiles.png");
	texture* manset = new texture(renderer, "Images/manguy.png");
	//spritesheet tilesheet(tileset);
	spritesheet mansheet(manset);

	bool quit = false;
	while (!quit)
	{
		//handle things
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		// do things	
		// render things
		SDL_RenderClear(renderer);

		//tilesheet.draw(0, 0, 0, renderer, camera);
		//tilesheet.draw(1, 32, 0, renderer, camera);
		//tilesheet.draw(2, 64, 0, renderer, camera);
		mansheet.draw(10, 10, 0, renderer, camera);
		SDL_RenderPresent(renderer);
	}
	close();
	return 0;
}