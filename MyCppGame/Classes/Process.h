#ifndef PROCESS_H
#define PROCESS_H
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "ProcessLayer.h"
#include "LogicGame.h"
class LogicGame;
extern LogicGame *logicgame;
USING_NS_CC;
class Process :public Scene
{
	public:
		virtual bool init();
		CREATE_FUNC(Process);
   
};
#endif // !PROCESS_H
