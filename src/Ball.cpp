#include "Ball.h"
#include "Utility.h"

const int WIDTH = 600;
const int HEIGHT = 400;

Ball::Ball(float x, float y, float m, Vector2D f) : position(x, y), velocity(0, 0), acceleration(0, 0)
{
	mass = m;

	acceleration = f;
	size = m / 2;

	angle = 0;
	angleVel = 0;
	angleAcc = 0;
}

void Ball::draw(SDL_Renderer* renderer)
{
	Vector2D vertex0 = Vector2D(size * 1.3, size * 1.3).RotTranslate(angle, position.getX(), position.getY());
	filledCircleRGBA(renderer, position.getX(), position.getY(), size, 255, 255, 255, 135);
	aacircleRGBA(renderer, position.getX(), position.getY(), size, 255, 255, 255, 255);
	lineRGBA(renderer, position.getX(), position.getY(), vertex0.getX(), vertex0.getY(), 255, 255, 255, 255);
}

void Ball::update()
{
	velocity += acceleration;
	position += velocity;

	angleAcc = size;
	angleVel += angleAcc;
	angleVel = Utility::constrain(angleVel, 0, 0.1);
	angle += angleVel;
	//printf("%f\n", angleAcc);

	acceleration *= 0;
}

void Ball::applyForce(Vector2D force)
{
	acceleration += force;
}

bool Ball::finished()
{
	return position.getY() > HEIGHT || position.getX() > WIDTH;
}