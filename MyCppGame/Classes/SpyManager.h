#ifndef SPY_MANAGER_H
#define SPY_MANAGER_H
#include "cocos2d.h"
#include "Spy.h"
#include "ProcessLayer.h"
#include "Config.h"
class ProcessLayer;
class Spy;
USING_NS_CC;
class SpyManager:public Object{
	private:
		Vector<Spy*> *childspy;
		ProcessLayer *layer;
		float PT_X;
		float PT_Y;
	public:
		SpyManager(ProcessLayer*);
		Spy* createSpy();
		void setChildSpy(Spy*);
		Vector<Spy*> *getChildSpy();
		Spy * getChildByTag(char*);
		Spy * getChildByBody(b2Body *body);
		Vector<Spy*> getManyChildByTag(char *tag);
		Sprite *createSprite(const std::string& filename, float x, float y, float width, float height, int order);

};
#endif
