#include "asteroid_B.h"

asteroid_B::asteroid_B(Vector2f position, Vector2f velocity, float level)
{
	theName = "asteroid";
	theVel = velocity;
	curLevel = level;
	asteroidAngle = 0;
	rSpeed = (float)random(-1, 1);
	theHP = 1;
	theShape.setPosition(position);
	theShape.setRadius(80);
	theShape.setOrigin(80.0f, 80.0f);
	theShape.setFillColor(Color::Red);
	theTex.loadFromFile("asteroid_b.png");
	theSprite.setTexture(theTex);
	theSprite.setPosition(position);
	theSprite.setOrigin(80.0f, 80.0f);
	theSprite.setRotation((float)random(0, 359));
}

void asteroid_B::draw()
{
	window.draw(theSprite);
}

void asteroid_B::update(float dt)
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

int asteroid_B::getRenderBucket()
{
	return 2;
}

void asteroid_B::checkCollisionWith(gameObject* obj)
{
	float d = length(getCenter() - obj->getCenter());
	float sum = theShape.getRadius() + obj->theShape.getRadius();

	if (d <= sum && obj->getName() == "asteroid")
	{
		theVel = { (float)random(-100, 100), (float)random(-100, 100) };
		obj->reDirection();
	}

	if (d <= sum && obj->getName() == "bullet")
	{
		hit();
		obj->hit();
	}
}