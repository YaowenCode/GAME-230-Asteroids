#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "gameObject.h"

#ifndef ASTEROID_S_H
#define ASTEROID_S_H

using namespace sf;

extern RenderWindow window;

class asteroid_S : public gameObject
{
private:
	float asteroidAngle;
	float rSpeed;
public:
	asteroid_S(Vector2f position, Vector2f velocity, float level);
	void draw();
	void update(float dt);
	int getRenderBucket();
	void checkCollisionWith(gameObject* obj);
};

#endif // !ASTEROID_S_H