#ifndef LEVEL_1_H
#define LEVEL_1_H
#include "cocos2d.h"
#include "ProcessLayer.h"
#include "Level.h"


class Level1:public Level{
  public:
	Level1(ProcessLayer*);
	virtual void create_level();
	virtual void contact_level(b2Contact*);
	virtual void update(float dt);
	virtual void refresh();
  private:
	SpyManager *spymanager;
	ProcessLayer* layer;
	b2World* world;
	float PT_X;
	float PT_Y;
};
#endif
