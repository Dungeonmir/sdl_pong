#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>

#include "RenderWindow.h"
#include "Entity.h"
#include "Physics.h"
#include "Text.h"
#include "Ball.h"

int main(int argc, char* argv[])
{

	std::string message = "0";
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();
	
	int screenWidth = 1280;
	int screenHeight = 800;
	
	int xMouse = 0;
	int yMouse = 0;
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "Hm STD_Init HAS FAILED(((  SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "Img_init has failed. Error: " << SDL_GetError() << std::endl;
	}
	
	if (TTF_Init() !=0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init error...");
		SDL_Quit();
		return 1;
	}
	RenderWindow window("I'm sure it's pong game", screenWidth, screenHeight);

	SDL_Texture* pong_ball = window.loadTexture("gfx/pong_ball.png");
	SDL_Texture* pong_platform = window.loadTexture("gfx/pong_platform.png");
	SDL_Texture* top_border = window.loadTexture("gfx/top_border.png");
	SDL_Texture* bottom_border = window.loadTexture("gfx/bottom_border.png");
	
	Entity etop_border(0, 0, top_border);
	Entity ebottom_border(0, screenHeight/4-6, bottom_border);
	Entity platform(0, 32, pong_platform);
	platform.setSize(14, 62);
	
	etop_border.setSize(320,6);
	ebottom_border.setSize(320, 6);
	
	Ball Gameball(window);
	Gameball.setX(64);
	Gameball.setY(64);


	const std::string resPath = "fonts/OldWizard.ttf";
	SDL_Color color= { 255,255,255,255 };
	SDL_Texture* text = renderText(message, resPath,color,16,window.getRenderer());
	int textW;
	int textH;
	SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
	int textX = screenWidth  / 8 - textW / 2;
	int textY = screenHeight / 8 - textH /2-80;

	SDL_RenderClear(window.getRenderer());
	Entity eText(textX, textY, text);
	eText.setSize(textW, textH);
	int count = 0;
	
	
	bool gameRunning = true;
	bool pause = true;
	SDL_Event event;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	while (gameRunning)
	{
		if (pause == true)
		{
			Gameball.StopMoving();
		}
		else if (pause == false)
		{
			Gameball.ContinueMoving();
		}
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float>elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			if (event.type ==SDL_KEYDOWN)
			{
				if (currentKeyStates[SDL_SCANCODE_Q])
				{
					gameRunning = false;
				}
				if (currentKeyStates[SDL_SCANCODE_SPACE])
				{
					if (pause == true) {pause = false;}
					else if (pause == false) {pause = true;}
				}
				if (currentKeyStates[SDL_SCANCODE_R])
				{
					std::cout << "Ball speed = " << Gameball.GetBallSpeed()<<std::endl;
					Gameball.IncreaseSpeed(200);
				}
				
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&xMouse, &yMouse);
				
			}
			if (event.type == SDL_WINDOWEVENT)
			{
				
					if(event.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						
						window.getWindowSize(&screenWidth, &screenHeight);
						std::cout <<"Weight "<< screenWidth << std::endl;
						std::cout <<"Height "<< screenHeight << std::endl;
					}
					if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED or 
						event.window.event == SDL_WINDOWEVENT_HIDDEN or 
						event.window.event == SDL_WINDOWEVENT_MINIMIZED or 
						event.window.event == SDL_WINDOWEVENT_MOVED or
						event.window.event == SDL_WINDOWEVENT_RESIZED
						)
					{
						pause = true;
					}
					
				
			}
			
		}
		window.clear();
		
		window.render(etop_border);
		window.render(ebottom_border);

		
		
			
		
				
		Gameball.countPosition(fElapsedTime);

		if (Gameball.getY() < 0)
		{
			Gameball.VerticalChangeDir();
		}
		
		

		if (Gameball.getY() > screenHeight / window.getMultiplier() - Gameball.getH())
		{

			Gameball.VerticalChangeDir();
			
		}
		
		

		if (Gameball.getX() <= 0)
		{					
			message = "Game over!";
			count = 0;
			text = renderText(message, resPath, color, 16, window.getRenderer());
			SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
			eText.setTex(text);
			eText.setSize(textW, textH);

			Gameball.setX(Gameball.getX() + 1);
			Gameball.HorizontalChangeDir();
		}
		
		

		if (Gameball.getX() > screenWidth/window.getMultiplier()-Gameball.getW())
		{

			Gameball.setX(Gameball.getX() - 1);
			Gameball.HorizontalChangeDir();
		}
		
		

		if (intersect(Gameball, etop_border) == true)
		{
			Gameball.setY(Gameball.getY() + 1);
			Gameball.VerticalChangeDir();
		}
		
		

		if (intersect(Gameball, ebottom_border) == true)
		{
			Gameball.setY(Gameball.getY() - 1);
			Gameball.VerticalChangeDir();
		}
		if (intersect(Gameball, platform) == true)
		{
			if (pause == false)
			{
				message = std::to_string(++count);
				text = renderText(message, resPath, color, 16, window.getRenderer());
				SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
				eText.setTex(text);
				eText.setSize(textW, textH);
				if (pause == false)
				{
					Gameball.IncreaseSpeed(50);
				}
				//Задать случайный угол 
				Gameball.SetBallAngle(((rand() % 75) + 25) * M_PI / 180);
			}
		}
				
		
			
		window.render(Gameball);
		
		
		if (yMouse/4 >= platform.getH()/2 and yMouse/4 <= screenHeight/4-platform.getH()/2)
		{
			platform.setY(yMouse / 4 - (platform.getH() / 2));
		}
		
		window.render(platform);
		window.render(eText);
		window.display();

	}
	window.cleanUp();
	SDL_Quit();
	return 0;
}