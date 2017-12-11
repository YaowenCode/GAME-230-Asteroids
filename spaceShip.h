#pragma once
#include <math.h>
#include "gameObject.h"

#ifndef SPACESHIP_H
#define SPACESHIP_H

using namespace sf;

extern RenderWindow window;

class spaceShip : public gameObject
{
	private:
		float acceleration;
		float turnSpeed;
		SoundBuffer bufferThrust;
		Sound soundThrust;
	public:
		spaceShip();
		void draw();
		void update(float dt);
		int getRenderBucket();
		void checkCollisionWith(gameObject* obj);
};

#endif // !SPACESHIP_H
