#include "MainScreen.h"
LogicGame *logicgame;
bool MainScreen::init()
{
	logicgame = new LogicGame();
	logicgame->loadDatabase();
	this->addChild(MainLayer::create());
	return true;
}
