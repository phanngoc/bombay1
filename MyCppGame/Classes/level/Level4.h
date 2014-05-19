#ifndef LEVEL_4_H
#define LEVEL_4_H
#include "cocos2d.h"
#include "ProcessLayer.h"
#include "Level.h"

class Level4 :public Level{
public:
	Level4(ProcessLayer*);
	void create_level();
	void contact_level(b2Contact*);
	void update(float dt);
	void refresh();
	void changeMass(b2Body *body, float mas);
	void doCallback(int swap);
private:
	SpyManager *spymanager;
	ProcessLayer* layer;
	b2World* world;
	float PT_X;
	float PT_Y;
	bool check_loop_change_mass = 1;
	int dem = 0;
};
#endif
