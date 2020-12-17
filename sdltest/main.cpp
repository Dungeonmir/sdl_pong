#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"


int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "Hm STD_Init HAS FAILED(((  SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "Img_init has failed. Error: " << SDL_GetError() << std::endl;
	}
	
	RenderWindow window("Looks like a game 100%", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("gfx/grass.png");

	Entity entities[4] = {
		Entity(0,0,grassTexture),
		Entity(0,32,grassTexture),
		Entity(32,0,grassTexture),
		Entity(32,32,grassTexture)
	};
	
	bool gameRunning = true;
	SDL_Event event;
	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			if (event.type ==SDL_KEYDOWN)
			{
				gameRunning = false;
			}
		}
		window.clear();
		for (int i = 0; i < 4; i++)
		{
			window.render(entities[i]);
		}
		
		
		window.display();

	}
	window.cleanUp();
	SDL_Quit();
	return 0;
}