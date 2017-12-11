#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "gameObject.h"

#ifndef BULLET_H
#define BULLET_H

using namespace sf;

extern RenderWindow window;

class bullet : public gameObject
{
	private:
		float bulletAngle;
	public:
		bullet(Vector2f position, Vector2f velocity, float angle);
		void draw();
		void update(float dt);
		int getRenderBucket();
		void checkCollisionWith(gameObject* obj);
};

#endif // !BULLET_H