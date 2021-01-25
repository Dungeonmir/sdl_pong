#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Entity.h"
class Text : public Entity
{
public:
	Text(SDL_Renderer* renderer_p);
	void print(std::string &message_p);
private:
	void renderText();
	std::string resPath;
	SDL_Color color;
	std::string message;
	int w;
	int h;
	int fontSize;
	SDL_Renderer* renderer;
};
