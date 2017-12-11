#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "gameObject.h"

#ifndef ASTEROID_M_H
#define ASTEROID_M_H

using namespace sf;

extern RenderWindow window;

class asteroid_M : public gameObject
{
	private:
		float asteroidAngle;
		float rSpeed;
	public:
		asteroid_M(Vector2f position, Vector2f velocity, float level);
		void draw();
		void update(float dt);
		int getRenderBucket();
		void checkCollisionWith(gameObject* obj);
};

#endif // !ASTEROID_M_H