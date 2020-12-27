#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

SDL_Texture* renderText(const std::string& message, const std::string& fontFile,
	SDL_Color color, int fontSize, SDL_Renderer* renderer);
