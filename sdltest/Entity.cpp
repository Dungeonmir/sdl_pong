#include "Entity.h"

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex)
{
	x = p_x;
	y = p_y;
	tex = p_tex;
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}
float Entity::getX()
{
	return x;
}
float Entity::getY()
{
	return y;
}
void Entity::setX(float temp_x)
{
	x = temp_x;
}
void Entity::setY(float temp_y)
{
	y = temp_y;
}
void Entity::setSize(int w, int h)
{
	currentFrame.w = w;
	currentFrame.h = h;
}
int Entity::getW()
{
	return currentFrame.w;
	
}
int Entity::getH()
{
	return currentFrame.h;
}
SDL_Texture* Entity::getTex()
{
	return tex;
}
SDL_Rect Entity::getCurrrentFrame()
{
	return currentFrame;
}