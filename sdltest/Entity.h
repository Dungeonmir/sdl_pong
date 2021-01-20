#pragma once
#include <SDL.h>
#include <SDL_image.h>




class Entity
{
public:
	Entity(float p_x, float p_y, SDL_Texture* p_t);
	Entity();
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	void setSize(int w, int h);
	int getW();
	int getH();
	void setTex(SDL_Texture* p_tex);
	SDL_Texture* getTex();
	SDL_Rect getCurrrentFrame();
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};