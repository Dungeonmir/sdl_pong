#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <chrono>

#include "RenderWindow.h"
#include "Entity.h"
#include "Physics.h"


int main(int argc, char* argv[])
{

	
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();
	
	int screenWidth = 1280;
	int screenHeight = 800;
	int ballRadius = 16;
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "Hm STD_Init HAS FAILED(((  SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "Img_init has failed. Error: " << SDL_GetError() << std::endl;
	}
	
	RenderWindow window("Looks like a game", screenWidth, screenHeight);

	SDL_Texture* pong_ball = window.loadTexture("gfx/pong_ball.png");
	SDL_Texture* pong_platform = window.loadTexture("gfx/pong_platform.png");
	SDL_Texture* top_border = window.loadTexture("gfx/top_border.png");
	SDL_Texture* bottom_border = window.loadTexture("gfx/bottom_border.png");
	
	Entity etop_border(0, 0, top_border);
	Entity ebottom_border(0, screenHeight/4-32, bottom_border);
	etop_border.setSize(320,32);
	ebottom_border.setSize(320, 32);
	
	std::vector<Entity> entities = {
	Entity (128,128, pong_ball)
	};
	std::vector<Entity> platforms = {
	Entity(64,32, pong_platform),
	Entity(128,32, pong_platform)
	};
	for (Entity& i : platforms)
	{
		
		i.setSize(32, 64);
	}
	//k  
	double ballAngle = M_PI / 6;
	float ballY = 50;
	float ballX = 80;
	float speed = 200.0f;
	bool gameRunning = true;
	SDL_Event event;
	while (gameRunning)
	{
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
				gameRunning = false;
			}
			if (event.type == SDL_WINDOWEVENT)
			{
					if(event.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						
						window.getWindowSize(&screenWidth, &screenHeight);
						std::cout <<"Weight "<< screenWidth << std::endl;
						std::cout <<"Height "<< screenHeight << std::endl;
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
				std::cout << ballAngle << "\n";
				i.setX(ballX);
				i.setY(ballY);
				if (ballY > screenHeight / window.getMultiplier() - i.getH())
				{
					ballAngle =M_PI - ballAngle;
					
				}
				std::cout << ballAngle << "\n";
				i.setX(ballX);
				i.setY(ballY);
				if (ballX <= 0)
				{
					ballAngle = 2*M_PI -ballAngle;
				}
				std::cout << ballAngle << "\n";
				i.setX(ballX);
				i.setY(ballY);
				if (ballX > screenWidth/window.getMultiplier()-i.getW())
				{
					ballAngle =2*M_PI - ballAngle ;
				}
				std::cout << ballAngle << "\n";
				i.setX(ballX);
				i.setY(ballY);
				if (intersect(i, etop_border) == true)
				{
					std::cout << " top ";
					ballAngle =  M_PI -  ballAngle;
				}
				std::cout << ballAngle << "\n";
				i.setX(ballX);
				i.setY(ballY);
				if (intersect(i, ebottom_border) == true)
				{
					std::cout << " bottom ";
					ballAngle = M_PI - ballAngle;
				}

				std::cout << ballAngle << "\n";
				i.setX(ballX);
				i.setY(ballY);
			
			window.render(i);
		}
		for (Entity& i : platforms)
		{
			window.render(i);
		}
		
		
		
		window.display();

	}
	window.cleanUp();
	SDL_Quit();
	return 0;
}