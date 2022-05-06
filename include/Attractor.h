#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "Vector2D.h"
#include "Mover.h"

class Attractor
{
public:
    Attractor(float x, float y, float m) : pos(x, y)
    {
        mass = m;
        r = sqrt(mass) * 2;
    }

    void attract(Mover* mover)
    {
        Vector2D force = pos - mover->GetPos();
        float distanceSq = force.constrainSquare(100, 1000);
        float pullingPower = 5;
        float strength = (pullingPower * mass * mover->GetMass()) / distanceSq;
        force.normalize();
        force *= strength;
        mover->applyForce(force);
    }

    void draw(SDL_Renderer* renderer)
    {
        filledCircleRGBA(renderer, pos.getX(), pos.getY(), r * 2, 255, 0, 100, 255);
    }

private:
    Vector2D pos = Vector2D(0, 0);
    float mass;
    float r;
};