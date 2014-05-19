#ifndef LOSELAYER_H
#define LOSELAYER_H
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "ProcessLayer.h"
#include "Config.h"
#include "LogicGame.h"
#include "LayerMenuLevel.h"
#include "MenuScreen.h"
#include "cocostudio\CocoStudio.h"
#include "ResourceManager.h"
using namespace cocostudio;
class LogicGame;
extern LogicGame *logicgame;
class LabelTTF;
class ProcessLayer;
class LoseLayer :public Layer{
	public:	
		LoseLayer(ProcessLayer *layer);
		static LoseLayer *init(ProcessLayer *hellobom);
		void refresh(Object* sender);
		void menu(Object *sender);
		void next(Object *sender);
		void callback2(Node *node,std::string);
		void callback3(Node *node);
	private:
		ProcessLayer  *layer;
};
#endif
