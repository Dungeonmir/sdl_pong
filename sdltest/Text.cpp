#include "Text.h"

Text::Text(SDL_Renderer* renderer_p)
{
	renderer = renderer_p;
	resPath = "fonts/OldWizard.ttf";
	color = { 255,255,255,255 };
	message = "*";
	this->setX(1280 / 8 - w / 2-32);
	this->setY(720 / 8 - h / 2 - 80);
	fontSize = 16;

	SDL_RenderClear(renderer_p);
}
void Text::renderText()
{
	//Открываем шрифт
	TTF_Font* font = TTF_OpenFont(resPath.c_str(), fontSize);
	if (font == nullptr) 
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_OpenFont error...");
		this->setTex(nullptr);
	}
	
	SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surface == nullptr) 
	{
		TTF_CloseFont(font);
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_RenderText error...(empty string)");
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "CreateTexture error...");
		this->setTex(nullptr);
	}

	//Очищаем поверхность и закрываем шрифт
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	this->setTex(texture);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	this->setSize(w, h);
}

void Text::print(std::string& message_p)
{
	message = message_p;
	renderText();
}
