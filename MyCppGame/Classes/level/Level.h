#ifndef LEVEL_H
#define LEVEL_H
#include "cocos2d.h"
#include "ProcessLayer.h"
using namespace cocos2d;
class Level{
	public:
		virtual void create_level() = 0;
		virtual void contact_level(b2Contact*)=0;
		virtual void update(float dt)=0;
		virtual void refresh()=0;
};
#endif