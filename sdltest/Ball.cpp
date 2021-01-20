#include "Ball.h"

Ball::Ball(RenderWindow p_window)
{
	setX(0);
	setY(0);
	setSize(32, 32);
	ballAngle = M_PI / 6;
	tempSpeed = 0.0f;
	fspeed = 200.0f;
	maxSpeed = 700;
	tempSpeed = 200.0f;
	p_window.getWindowSize(&screenWidth, &screenHeight);
	
	setTex(p_window.loadTexture("gfx/pong_ball.png"));
	
	
}

void Ball::countPosition(float fElapsedTime)
{
	setX( getX() + (fspeed * fElapsedTime * SDL_sin(ballAngle)));
	setY( getY() + (fspeed * fElapsedTime * SDL_cos(ballAngle)));
}
void Ball::IncreaseSpeed(int increaseStep)
{
	if(fspeed<maxSpeed)
		fspeed += increaseStep;
}
void Ball::VerticalChangeDir()
{
	ballAngle = M_PI - ballAngle;
}
void Ball::HorizontalChangeDir()
{
	ballAngle = 2 * M_PI - ballAngle;
}

void Ball::SetBallAngle(float newBallAngle)
{
	ballAngle = newBallAngle;
}
void Ball::StopMoving()
{
	if (fspeed > 0)
	{
		tempSpeed = fspeed;
		fspeed = 0;
	}
	
	//fspeed = 0;
}

void Ball::ContinueMoving()
{
	fspeed = tempSpeed;
}


float Ball::GetBallSpeed()
{
	return fspeed;
}






