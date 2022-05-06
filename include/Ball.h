#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include "Vector2D.h"

class Ball
{
public:
	Ball(float x, float y, float m, Vector2D f);
	void draw(SDL_Renderer* renderer);
	void update();
	void applyForce(Vector2D force);
	bool finished();

	float mass;
private:
	float angle;
	float angleVel;
	float angleAcc;

	float size;

	Vector2D acceleration = Vector2D(0, 0);
	Vector2D velocity = Vector2D(0, 0);
	Vector2D position = Vector2D(0, 0);
};