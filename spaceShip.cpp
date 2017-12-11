#include "spaceShip.h"

spaceShip::spaceShip()
{
	theHP = 1;
	theName = "spaceShip";
	acceleration = 0.07f;
	turnSpeed = 0.10f;
	theSprite.setPosition(800, 450);
	theShape.setPosition(800, 450);
	theSprite.setRotation(0.0f);
	theShape.setRadius(30.0f);
	theShape.setOrigin(30.0f, 30.0f);
	theShape.setFillColor(Color::Red);
	theTex.loadFromFile("spaceShip.png");
	theSprite.setTexture(theTex);
	theSprite.setOrigin(30.0f, 27.0f);
	bufferThrust.loadFromFile("thrust.wav");
	soundThrust.setBuffer(bufferThrust);
}

void spaceShip::draw()
{
	window.draw(theSprite);
}

void spaceShip::update(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (soundThrust.getStatus() != Sound::Playing)
		{
			soundThrust.play();
		}

		float angle = (float)(3.1415926 * theSprite.getRotation()) / 180;

		theForce.x = std::sin(angle);
		theForce.y = -1 * std::cos(angle);

		theForce *= acceleration * dt;
		theVel += theForce;
	}

	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
	{
		theSprite.setRotation(theSprite.getRotation() + -1 * turnSpeed * dt * 1000);
	}

	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		theSprite.setRotation(theSprite.getRotation() + turnSpeed * dt * 1000);
	}

	if (theSprite.getPosition().x >= 1600)
	{
		theSprite.setPosition(1, theSprite.getPosition().y);
	}
	if (theSprite.getPosition().x <= 0)
	{
		theSprite.setPosition(1599, theSprite.getPosition().y);
	}
	if (theSprite.getPosition().y >= 900)
	{
		theSprite.setPosition(theSprite.getPosition().x, 1);
	}
	if (theSprite.getPosition().y <= 0)
	{
		theSprite.setPosition(theSprite.getPosition().x, 899);
	}

	theSprite.move(theVel);
	theShape.setPosition(theSprite.getPosition());
}

int spaceShip::getRenderBucket()
{
	return 0;
}

void spaceShip::checkCollisionWith(gameObject* obj)
{
	float d = length(getCenter() - obj->getCenter());
	float sum = theShape.getRadius() + obj->theShape.getRadius();

	if (d < sum + 3 && obj->getName() == "asteroid")
	{
		obj->reDirection();
		hit();
	}
}