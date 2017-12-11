#include "gameObject.h"

float gameObject::length(Vector2f v)
{
	return sqrtf(v.x*v.x + v.y*v.y);
}

bool gameObject::isDead()
{
	if (theHP <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void gameObject::hit()
{
	 theHP -= 1;
}

void gameObject::killObject()
{
	theShape.~CircleShape();
	theName.~basic_string();
	theTex.~Texture();
}

void gameObject::reset()
{
	theHP += 1;
	theSprite.setPosition(800, 450);
	theVel = { 0, 0 };
}

void gameObject::reDirection()
{
	theVel = -theVel;
}

int gameObject::getHP()
{
	return theHP;
}

string gameObject::getName()
{
	return theName;
}

float gameObject::getRotation()
{
	return theSprite.getRotation();
}

Vector2f gameObject::getCenter()
{
	return theShape.getPosition();
}

Vector2f gameObject::getVelocity()
{
	return theVel;
}

Vector2f gameObject::getPosition()
{
	return theShape.getPosition();
}