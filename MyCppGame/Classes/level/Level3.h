#ifndef LEVEL_3_H
#define LEVEL_3_H
#include "cocos2d.h"
#include "ProcessLayer.h"
#include "Level.h"

class Level3 :public Level{
public:
	Level3(ProcessLayer*);
	virtual void create_level();
	virtual void contact_level(b2Contact*);
	virtual void update(float dt);
	virtual void refresh();
	void doCallback(b2Joint *joint);
private:
	SpyManager *spymanager;
	ProcessLayer* layer;
	b2World* world;
	float PT_X;
	float PT_Y;
};
#endif
