#include "RenderWindow.h"
#include "Entity.h"
#include <iostream>
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
SDL_Texture* RenderWindow::loadTexture(const char* p_filepath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filepath);

	if (texture == NULL)
	{
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}
void RenderWindow::getWindowSize(int* p_w, int* p_h)
{
	SDL_GetWindowSize(window, p_w, p_h);
}
Uint32 RenderWindow::getWindowID()
{
	return SDL_GetWindowID(window);
}
void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear() 
{
	SDL_RenderClear(renderer);
}
void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrrentFrame().x;
	src.y = p_entity.getCurrrentFrame().y;
	src.w = p_entity.getCurrrentFrame().w;
	src.h = p_entity.getCurrrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX() * multiplier;
	dst.y = p_entity.getY() * multiplier;
	dst.w = p_entity.getCurrrentFrame().w * multiplier;
	dst.h = p_entity.getCurrrentFrame().h * multiplier;
	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
float RenderWindow::getMultiplier()
{
	return RenderWindow::multiplier;
}
