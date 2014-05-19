#ifndef PROCESS_LAYER_H
#define PROCESS_LAYER_H
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Config.h"
#include "Spy.h"
#include "ControlListener.h"
#include "SpyManager.h"
#include "ControlLevel.h"
#include "LogicGame.h"
class LogicGame;
extern LogicGame *logicgame;
class ControlLevel;
USING_NS_CC;
class Spy;
class SpyManager;

class ProcessLayer :public Layer
{
	public:	
		static ProcessLayer *createLayer(int level);
		void initBackground();
		void update(float dt);
		void updateCheck(float dt);
		void updateAll(float dt);
		b2World *getWorld();
		SpyManager* getSpyManager();
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
		void onTouchesMoved(Touch *touch, Event *unused_event);
		void refresh(bool);
		~ProcessLayer();
		void onExit();
		void startCheck();
		void setControlLevel(ControlLevel *);
		ControlLevel *getControlLevel();
	private:
		b2World *world;

		Sprite *button_fire;

		Sprite *button_refresh;

		SpyManager *spymanager;

		Spy *spy_temp = nullptr;

		bool check_fire = 0;

		bool check_move = 0;

		float PT_X;
		float PT_Y;

		EventListenerTouchOneByOne* touchListener;

		ControlLevel *controlLevel;
};
#endif