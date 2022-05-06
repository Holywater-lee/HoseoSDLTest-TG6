#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include "Vector2D.h"

class Walker
{
public:
	Walker();
	void draw(SDL_Renderer* renderer);
	void update();
	void applyForce(Vector2D force);
	void turn(float a);
	void thrust();
	void wrapEdges();
	Vector2D GetPos() const { return location; }

private:
	Vector2D acceleration = Vector2D(0, 0);
	Vector2D velocity = Vector2D(0, 0);
	Vector2D location = Vector2D(0, 0);
	const int r = 16;
	const float damping = 0.995;
	const float topSpeed = 6;
	bool thrusting = false;
	float heading = 0;
};