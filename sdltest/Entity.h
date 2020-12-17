#pragma once
#include <SDL.h>
#include <SDL_image.h>




class Entity
{
public:
	Entity(float p_x, float p_y, SDL_Texture* p_t);
	float getX();
	float getY();
	SDL_Texture* getTex();
	SDL_Rect getCurrrentFrame();
private:
	double x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};