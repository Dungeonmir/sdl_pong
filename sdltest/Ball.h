#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "RenderWindow.h"
#include "Physics.h"
class Ball : public Entity
{
	

public:
	Ball(RenderWindow p_window);
	void countPosition(float fElapsedTime);
	void IncreaseSpeed(int increaseStep);
	void VerticalChangeDir();
	void HorizontalChangeDir();
	void SetBallAngle(float newBallAngle);
	void StopMoving();
	void ContinueMoving();
	float GetBallSpeed();
private:
	int screenWidth;
	int screenHeight;
	int count = 0;
	double ballAngle = M_PI / 6;
	float fspeed = 200.0f;
	int maxSpeed = 700;
	float tempSpeed = 200.0f;
	
};
