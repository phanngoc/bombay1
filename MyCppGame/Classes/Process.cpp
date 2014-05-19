#include "Process.h"
bool Process::init()
{
	ProcessLayer *layer = ProcessLayer::createLayer(logicgame->getLevelPlaying());
	this->addChild(layer);
	return true;
}