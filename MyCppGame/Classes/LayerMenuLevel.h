#ifndef LAYER_MENU_LEVEL_H
#define LAYER_MENU_LEVEL_H
#include "cocos2d.h"
#include "SlidingMenu.h"
#include "LogicGame.h"
#include "Config.h"
#include "Process.h"
#include "ResourceManager.h"
#include "WrapSlidingMenu.h"
#include "MainScreen.h"
class LogicGame;
extern LogicGame *logicgame;
USING_NS_CC;
class LayerMenuLevel :public Layer
{
	public:
		virtual bool init();
		CREATE_FUNC(LayerMenuLevel);
		void gridClickedCallBack(Ref*,int);
		void backCallback();
		~LayerMenuLevel();
};
#endif

