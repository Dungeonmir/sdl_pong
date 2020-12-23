#include "Physics.h"

bool intersect(Entity e1, Entity e2)
{
	float r1x1 = e1.getX();
	float r1y1 = e1.getY();
	float r1x2 = e1.getCurrrentFrame().w + r1x1;
	float r1y2 = e1.getCurrrentFrame().h + r1y1;
	float r2x1 = e2.getX();
	float r2y1 = e2.getY();
	float r2x2 = e2.getCurrrentFrame().w + r2x1;
	float r2y2 = e2.getCurrrentFrame().h + r2y1;

	if (
		r1x1 < r2x2 &&
		r1x2 > r2x1 &&
		r1y1 < r2y2 &&
		r1y2 > r2y1
		)
	{
		return true;
	}
	else return false;
}
