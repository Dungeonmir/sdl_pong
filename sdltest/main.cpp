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
	RenderWindow window("Looks like a game", screenWidth, screenHeight);

	SDL_Texture* pong_ball = window.loadTexture("gfx/pong_ball.png");
	SDL_Texture* pong_platform = window.loadTexture("gfx/pong_platform.png");
	SDL_Texture* top_border = window.loadTexture("gfx/top_border.png");
	SDL_Texture* bottom_border = window.loadTexture("gfx/bottom_border.png");
	
	Entity etop_border(0, 0, top_border);
	Entity ebottom_border(0, screenHeight/4-32, bottom_border);
	Entity platform(0, 32, pong_platform);
	platform.setSize(32, 64);
	platform.setX(-8);
	etop_border.setSize(320,32);
	ebottom_border.setSize(320, 32);
	
	std::vector<Entity> entities = {
	Entity (128,128, pong_ball)
	};
	  
	const std::string resPath = "fonts/dungeonmir.ttf";
	SDL_Color color= { 255,255,255,255 };
	SDL_Texture* image = renderText(message, resPath,color,16,window.getRenderer());
	int imageW;
	int imageH;
	SDL_QueryTexture(image, NULL, NULL, &imageW, &imageH);
	int imageX = screenWidth  / 8 - imageW / 2;
	int imageY = screenHeight / 8 - imageH /2-80;

	SDL_RenderClear(window.getRenderer());
	Entity e_image(imageX, imageY, image);
	e_image.setSize(imageW, imageH);
	int count = 0;
	
	double ballAngle = M_PI / 6;
	float ballY = 50;
	float ballX = 80;
	float speed = 0.0f;
	float fspeed = 200.0f;
	int maxSpeed = 700;
	bool gameRunning = true;
	bool pause = true;
	SDL_Event event;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	while (gameRunning)
	{
		if (pause == true)
		{
			speed = 0;
		}
		else if (pause == false)
		{
			speed = fspeed;
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
					std::cout << "Ball speed = " << speed<<std::endl;
					fspeed += 200.0f;
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

		for (Entity& i : entities)
		{
				
			
				ballX += speed * fElapsedTime * SDL_sin(ballAngle);
				ballY += speed * fElapsedTime * SDL_cos(ballAngle);
				
				
				if (ballY < 0)
				{
					
					ballAngle = M_PI - ballAngle;
				}
				
				i.setX(ballX);
				i.setY(ballY);
				if (ballY > screenHeight / window.getMultiplier() - i.getH())
				{

					ballAngle =M_PI - ballAngle;
					
				}
				
				i.setX(ballX);
				i.setY(ballY);
				if (ballX <= 0)
				{
					ballX += 1;
					ballAngle = 2 * M_PI - ballAngle;
				}
				
				i.setX(ballX);
				i.setY(ballY);
				if (ballX > screenWidth/window.getMultiplier()-i.getW())
				{
					ballX -= 1;
					ballAngle =2*M_PI - ballAngle ;
				}
				
				i.setX(ballX);
				i.setY(ballY);
				if (intersect(i, etop_border) == true)
				{
					ballY += 1;
					
					ballAngle =  M_PI -  ballAngle;
				}
				
				i.setX(ballX);
				i.setY(ballY);
				if (intersect(i, ebottom_border) == true)
				{
					ballY -= 1;
					
					ballAngle = M_PI - ballAngle;
				}
				if (intersect(i, platform) == true)
				{
					message = std::to_string(++count);
					image = renderText(message, resPath, color, 16, window.getRenderer());
					SDL_QueryTexture(image, NULL, NULL, &imageW, &imageH);
					e_image.setTex(image);
					e_image.setSize(imageW, imageH);
					if (fspeed < maxSpeed && pause ==false)
					{
						fspeed += 50;
					}
					
					ballAngle = ((rand() % 75) + 25)*M_PI/180;
					
				}
				
				i.setX(ballX);
				i.setY(ballY);
			
			window.render(i);
		}
		
			
			platform.setY(yMouse/4-(platform.getH()/2));
			window.render(platform);
			window.render(e_image);
		
		
		
		
		window.display();

	}
	window.cleanUp();
	SDL_Quit();
	return 0;
}