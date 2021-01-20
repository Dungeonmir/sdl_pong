#include "Text.h"

SDL_Texture* renderText(const std::string & message, const std::string& fontFile,
	SDL_Color color, int fontSize, SDL_Renderer* renderer)
{
	//Открываем шрифт
	TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr) 
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_OpenFont error...");
		return nullptr;
	}
	
	SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surface == nullptr) 
	{
		TTF_CloseFont(font);
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_RenderText error...");
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "CreateTexture error...");
	}

	//Очищаем поверхность и закрываем шрифт
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}
