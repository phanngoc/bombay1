#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "cocos2d.h"
#include "LayerMenuLevel.h"
USING_NS_CC;
class MenuScreen :public Scene{
	public:
		CREATE_FUNC(MenuScreen);
		virtual bool init();
};
#endif
