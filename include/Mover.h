#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "Vector2D.h"

class Mover
{
public:
	Mover(float x, float y, float m);
	void draw(SDL_Renderer* renderer);
	void update();
	void applyForce(Vector2D force);
	Vector2D GetPos() const { return pos; }
	float GetMass() const { return mass; }

private:
	Vector2D acceleration = Vector2D(0, 0);
	Vector2D velocity = Vector2D(0, 0);
	Vector2D pos = Vector2D(0, 0);

	float angle;
	float mass;
	float r;
};