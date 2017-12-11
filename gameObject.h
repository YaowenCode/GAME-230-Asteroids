#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <ctime>
#include <cstdlib>
#define random(a, b) (rand()%(b - a + 1) + a)

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

using namespace sf;
using namespace std;

class gameObject
{
	protected:
		int theHP;
		float curLevel;
		string theName;
		Vector2f theVel;
		Vector2f theForce;
		Texture theTex;
		Sprite theSprite;
		float length(Vector2f v);
	public:
		CircleShape theShape;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		virtual int getRenderBucket() = 0;
		virtual void checkCollisionWith(gameObject* obj) = 0;
		bool isDead();
		void hit();
		void killObject();
		void reset();
		void reDirection();
		int getHP();
		string getName();
		float getRotation();
		Vector2f getCenter();
		Vector2f getVelocity();
		Vector2f getPosition();
};

#endif // !GAMEOBJECT_H