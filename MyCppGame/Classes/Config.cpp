#include "Config.h"
Config *Config::init()
{
	Config *config = new Config();
	config->autorelease();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	config->setPTX(visibleSize.width / 10);
	config->setPTY(visibleSize.height / 7.5);
	return config;
}
float Config::getPTX()
{
	return PT_X;
}
float Config::getPTY()
{
	return PT_Y;
}
void Config::setPTX(float ptx)
{
	PT_X = ptx;
}
void Config::setPTY(float pty)
{
	PT_Y = pty;
}

