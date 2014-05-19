#ifndef CONTROL_LEVEL_H
#define CONTROL_LEVEL_H
#include "cocos2d.h"
#include "Config.h"
#include "Box2D\Box2D.h"
#include "ProcessLayer.h"
#include "Spy.h"
#include "cocostudio\CocoStudio.h" 
#include "LogicGame.h"
#include "SpyManager.h"
#include "level/Level.h"
#include "level/Level1.h"
#include "level/Level2.h"
#include "level/Level3.h"
#include "level/Level4.h"
#include "level/Level5.h"
#include "level/Level6.h"

class SpyManager;
class LogicGame;
extern LogicGame *logicgame;
using namespace cocostudio;
USING_NS_CC;
class ControlLevel{
	public:
		ControlLevel(int,ProcessLayer*);
		~ControlLevel();
		static ControlLevel *init(int, ProcessLayer*);
		void refresh();
		void initContact(b2Contact *contact);
		void initUpdate(float dt);
	private:
		int level;
		ProcessLayer* layer;
		Level *clevel;
};
#endif
