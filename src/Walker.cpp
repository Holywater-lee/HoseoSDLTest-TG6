#include "Walker.h"
#include <math.h>

const int WIDTH = 600;
const int HEIGHT = 400;

Walker::Walker() : location(WIDTH / 2, HEIGHT / 2), velocity(0, 0), acceleration(0, 0)
{
	//printf("위치: (%f, %f)\n", location.getX(), location.getY());

	thrusting = false;
	heading = 0;
}

void Walker::update()
{
	velocity += acceleration;
	velocity *= damping;
	velocity.limit(topSpeed);
	location += velocity;
	acceleration *= 0;
}

void Walker::applyForce(Vector2D force)
{
	acceleration += force;
}

void Walker::turn(float a)
{
	heading += a;
}

void Walker::thrust()
{
	//float angle = heading - 3.1415926535 / 2;
	Vector2D force = Vector2D(cos(heading), sin(heading));
	force *= 0.1;
	applyForce(force);
	thrusting = true;
}

void Walker::wrapEdges()
{
	float buffer = r * 2;
	if (location.getX() > WIDTH + buffer) location.setX(-buffer);
	else if (location.getX() < -buffer) location.setX(WIDTH + buffer);
	if (location.getY() > HEIGHT + buffer) location.setY(-buffer);
	else if (location.getY() < -buffer) location.setY(HEIGHT + buffer);
}

void Walker::draw(SDL_Renderer* renderer)
{
	Vector2D circleVertex0 = Vector2D(-r * 1.5, r / 3 * 2).RotTranslate(heading, location.getX(), location.getY());
	Vector2D circleVertex1 = Vector2D(-r * 1.5, -r / 3 * 2).RotTranslate(heading, location.getX(), location.getY());

	filledCircleRGBA(renderer, circleVertex0.getX(), circleVertex0.getY(), r / 4, !thrusting ? 125 : 255, !thrusting ? 125 : 0, !thrusting ? 125 : 0, 255);
	filledCircleRGBA(renderer, circleVertex1.getX(), circleVertex1.getY(), r / 4, !thrusting ? 125 : 255, !thrusting ? 125 : 0, !thrusting ? 125 : 0, 255);
	aacircleRGBA(renderer, circleVertex0.getX(), circleVertex0.getY(), r / 4, 255, 255, 255, 255);
	aacircleRGBA(renderer, circleVertex1.getX(), circleVertex1.getY(), r / 4, 255, 255, 255, 255);

	Vector2D vertex0 = Vector2D(r, 0).RotTranslate(heading, location.getX(), location.getY());
	Vector2D vertex1 = Vector2D(-r, -r).RotTranslate(heading, location.getX(), location.getY());
	Vector2D vertex2 = Vector2D(-r, r).RotTranslate(heading, location.getX(), location.getY());

	filledTrigonRGBA(renderer, vertex0.getX(), vertex0.getY(), vertex1.getX(), vertex1.getY(), vertex2.getX(), vertex2.getY(), 125, 125, 125, 255);
	aatrigonRGBA(renderer, vertex0.getX(), vertex0.getY(), vertex1.getX(), vertex1.getY(), vertex2.getX(), vertex2.getY(), 255, 255, 255, 255);

	thrusting = false;
}
