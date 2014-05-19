#include "helper.h"


float x(float x)
{
	float PT_X = logicgame->getPTX();
	return PT_X*x;
}

float y(float y)
{
	float PT_Y = logicgame->getPTY();
	return PT_Y*y;
}


void _size(Node *sprite, float _x, float _y, float _width, float _height)
{
	sprite->setPosition(x(_x), y(_y));
	sprite->setScale(x(_width) / sprite->getContentSize().width, y(_height) / sprite->getContentSize().height);
}

