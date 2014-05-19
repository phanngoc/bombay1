#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H
#include "cocos2d.h"
#include "LogicGame.h"
#include "MainLayer.h"
#include "helper.h"
USING_NS_CC;
class MainScreen :public Scene{
	public:
		virtual bool init();
		CREATE_FUNC(MainScreen);
};
#endif
