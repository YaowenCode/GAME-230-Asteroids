#include "bullet.h"

bullet::bullet(Vector2f position, Vector2f velocity, float angle)
{
	theHP = 1;
	theName = "bullet";
	bulletAngle = (float)(3.1415926 * angle) / 180;
	theForce.x = std::sin(bulletAngle) / 3;
	theForce.y = -1 * std::cos(bulletAngle) / 3;
	theVel = velocity + theForce;
	theTex.loadFromFile("bullet.png");
	theShape.setRadius(7.5f);
	theShape.setFillColor(Color::Red);
	theShape.setOrigin(7.5f, 7.5f);
	theShape.setPosition(position);
	theSprite.setPosition(position);
	theSprite.setOrigin(7.5f, 7.5f);
	theSprite.setTexture(theTex);
}

void bullet::draw()
{
	window.draw(theSprite);
}

void bullet::update(float dt)
{
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

int bullet::getRenderBucket()
{
	return 1;
}

void bullet::checkCollisionWith(gameObject* obj)
{

}