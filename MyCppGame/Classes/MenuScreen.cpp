#include "MenuScreen.h"

bool MenuScreen::init()
{
	LayerMenuLevel *layer = LayerMenuLevel::create();
	this->addChild(layer);
	return true;
}

