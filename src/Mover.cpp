#include "Mover.h"
#include "Utility.h"
#include <math.h>

Mover::Mover(float x, float y, float m) : pos(x, y), velocity(Utility::GetRandomFloat(-1, 1), Utility::GetRandomFloat(-1, 1)), acceleration(0, 0)
{
	velocity *= 5;
	mass = m;
	if (m == 0) mass = 0.00000001;
	r = sqrt(mass) * 2;
	angle = 0;
}

void Mover::update()
{
	velocity += acceleration;
	pos += velocity;
	acceleration *= 0;
	angle = atan2(velocity.getY(), velocity.getX());
}

void Mover::applyForce(Vector2D force)
{
	Vector2D newForce = force;

	newForce /= mass;
	acceleration += newForce;
}

void Mover::draw(SDL_Renderer* renderer)
{
	Vector2D vertex0 = Vector2D(r, 0).RotTranslate(angle, pos.getX(), pos.getY());
	Vector2D vertex1 = Vector2D(-r, -r / 2).RotTranslate(angle, pos.getX(), pos.getY());
	Vector2D vertex2 = Vector2D(-r, r / 2).RotTranslate(angle, pos.getX(), pos.getY());

	filledTrigonRGBA(renderer, vertex0.getX(), vertex0.getY(), vertex1.getX(), vertex1.getY(), vertex2.getX(), vertex2.getY(), 255, 255, 255, 100);
	aatrigonRGBA(renderer, vertex0.getX(), vertex0.getY(), vertex1.getX(), vertex1.getY(), vertex2.getX(), vertex2.getY(), 255, 255, 255, 255);
}