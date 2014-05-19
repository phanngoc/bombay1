#ifndef MAIN_LAYER_H
#define MAIN_LAYER_H
#include "cocos2d.h"
#include "MenuScreen.h"
#include "ResourceManager.h"
#include "Config.h"

USING_NS_CC;
class MainLayer :public Layer{
	public:
		virtual bool init();
		CREATE_FUNC(MainLayer);
		void menu_play();
		void menu_option();
		void menu_exit();
};
#endif
