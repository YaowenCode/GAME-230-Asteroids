#include "asteroid_M.h"

asteroid_M::asteroid_M(Vector2f position, Vector2f velocity, float level)
{
	theName = "asteroid";
	theVel = velocity;
	asteroidAngle = 0;
	curLevel = level;
	rSpeed = (float)random(-1, 1);
	theHP = 1;
	theShape.setPosition(position);
	theShape.setRadius(40);
	theShape.setOrigin(40.0f, 40.0f);
	theShape.setFillColor(Color::Red);
	theTex.loadFromFile("asteroid_m.png");
	theSprite.setTexture(theTex);
	theSprite.setPosition(position);
	theSprite.setOrigin(40.0f, 40.0f);
	theSprite.setRotation((float)random(0, 359));
}

void asteroid_M::draw()
{
	window.draw(theSprite);
}

void asteroid_M::update(float dt)
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

int asteroid_M::getRenderBucket()
{
	return 3;
}

void asteroid_M::checkCollisionWith(gameObject* obj)
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