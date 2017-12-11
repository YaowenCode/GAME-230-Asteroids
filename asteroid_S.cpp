#include "asteroid_S.h"

asteroid_S::asteroid_S(Vector2f position, Vector2f velocity, float level)
{
	theName = "asteroid";
	theVel = velocity;
	curLevel = level;
	asteroidAngle = 0;
	rSpeed = (float)random(-1, 1);
	theHP = 1;
	theShape.setPosition(position);
	theShape.setRadius(20);
	theShape.setOrigin(20.0f, 20.0f);
	theShape.setFillColor(Color::Red);
	theTex.loadFromFile("asteroid_s.png");
	theSprite.setTexture(theTex);
	theSprite.setPosition(position);
	theSprite.setOrigin(20.0f, 20.0f);
	theSprite.setRotation((float)random(0, 359));
}

void asteroid_S::draw()
{
	window.draw(theSprite);
}

void asteroid_S::update(float dt)
{
	if (asteroidAngle >= 359)
	{
		asteroidAngle = 0;
	}
	else
	{
		++asteroidAngle;
	}

	theSprite.rotate(asteroidAngle * dt * rSpeed);

	if (theSprite.getPosition().x >= 1600 - theShape.getRadius() / 2)
	{
		theSprite.setPosition(theShape.getRadius() / 2, theSprite.getPosition().y);
	}
	if (theSprite.getPosition().x < theShape.getRadius() / 2)
	{
		theSprite.setPosition(1600 - theShape.getRadius() / 2, theSprite.getPosition().y);
	}
	if (theSprite.getPosition().y >= 900 - theShape.getRadius() / 2)
	{
		theSprite.setPosition(theSprite.getPosition().x, theShape.getRadius() / 2);
	}
	if (theSprite.getPosition().y < theShape.getRadius() / 2)
	{
		theSprite.setPosition(theSprite.getPosition().x, 900 - theShape.getRadius() / 2);
	}

	theSprite.move(theVel * dt * curLevel);
	theShape.setPosition(theSprite.getPosition());
}

int asteroid_S::getRenderBucket()
{
	return 4;
}

void asteroid_S::checkCollisionWith(gameObject* obj)
{
	float d = length(getCenter() - obj->getCenter());
	float sum = theShape.getRadius() + obj->theShape.getRadius();

	if (d <= sum && obj->getName() == "asteroid")
	{
		theVel = { (float)random(-100, 100), (float)random(-100, 100) };
	}

	if (d <= sum && obj->getName() == "bullet")
	{
		hit();
		obj->hit();
	}
}