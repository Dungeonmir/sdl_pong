#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "Entity.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();
	void getWindowSize(int* p_w, int* p_h);
	Uint32 getWindowID();
	float getMultiplier();
private:
	float multiplier = 4;
	SDL_Window* window;
	SDL_Renderer* renderer;

};
