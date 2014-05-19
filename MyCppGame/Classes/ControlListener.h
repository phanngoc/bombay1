#ifndef CONTROL_LISTENER_H
#define CONTROL_LISTENER_H
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "ProcessLayer.h"
#include "Spy.h"
#include "LogicGame.h"
#include "LoseLayer.h"
#include "SpyManager.h"
class SpyManager;
class LoseLayer;
class LogicGame;
extern LogicGame* logicgame;
class Spy;
class ProcessLayer;

class ControlListener 
{
	public:
		ControlListener(ProcessLayer*);
	private:
		ProcessLayer* layer;
		SpyManager *spymanager;
};
#endif

