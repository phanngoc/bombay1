#include "MainLayer.h"

bool MainLayer::init()
{
	Size back = Director::getInstance()->getVisibleSize();
	ResourceManager *res = ResourceManager::init("all");
	Sprite *background = Sprite::create(res->get("background_main"));
	background->setScale(back.width / background->getContentSize().width, back.height / background->getContentSize().height);
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	this->addChild(background,0);
	MenuItemImage *menu_option = MenuItemImage::create(res->get("menu_main_option"), res->get("menu_main_option"), res->get("menu_main_option"),CC_CALLBACK_0(MainLayer::menu_option,this));
	_size(menu_option, 1.8, 2, 1.5,1);
	MenuItemImage *menu_play = MenuItemImage::create(res->get("menu_main_play"), res->get("menu_main_play"), res->get("menu_main_play"), CC_CALLBACK_0(MainLayer::menu_play, this));
	_size(menu_play, 5, 2.4,2, 1.25);
	MenuItemImage *menu_exit = MenuItemImage::create(res->get("menu_main_exit"), res->get("menu_main_exit"), res->get("menu_main_exit"), CC_CALLBACK_0(MainLayer::menu_exit, this));
	_size(menu_exit,8.2, 2,1.5, 1);
	Menu *menu = Menu::create();
	menu->addChild(menu_option);
	menu->addChild(menu_play);
	menu->addChild(menu_exit);
	menu->setAnchorPoint(Point(0, 0));
	menu->setPosition(0, 0);
	this->addChild(menu,5);
	delete res;
	return true;
}

void MainLayer::menu_play()
{
	Director::getInstance()->replaceScene(MenuScreen::create());
}
void MainLayer::menu_option()
{

}
void MainLayer::menu_exit()
{
	Director::getInstance()->end();
}