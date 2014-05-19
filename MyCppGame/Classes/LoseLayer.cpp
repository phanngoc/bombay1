#include "LoseLayer.h"

LoseLayer::LoseLayer(ProcessLayer *layer) :layer(layer)
{
	float PT_X = logicgame->getPTX();
	float PT_Y = logicgame->getPTY();

	MenuItem *refresh = MenuItemImage::create("refresh_button.png", "refresh_button.png", CC_CALLBACK_1(LoseLayer::refresh, this));
	refresh->setScale(1.0f*PT_X / refresh->getContentSize().width, 1.0f*PT_Y / refresh->getContentSize().height);
	refresh->setPosition(5.0f*PT_X, 3.0f*PT_Y);

	MenuItem *menu = MenuItemImage::create("button_menu.png", "button_menu.png", CC_CALLBACK_1(LoseLayer::menu, this));
	menu->setScale(1.0f*PT_X / menu->getContentSize().width, 1.0f*PT_Y/ menu->getContentSize().height);
	menu->setPosition(3.5f*PT_X,3.0f*PT_Y);
	MenuItem *next = MenuItemImage::create("next_button.png", "next_button.png", CC_CALLBACK_1(LoseLayer::next, this));
	next->setScale(1.0f*PT_X / next->getContentSize().width, 1.0f*PT_Y / next->getContentSize().height);
	next->setPosition(6.5f*PT_X, 3.0f*PT_Y);

	MenuItem *ground_menu = MenuItemImage::create("background_menu_lose.png", "background_menu_lose.png");
	ground_menu->setScale(5 * PT_X / ground_menu->getContentSize().width, 4 * PT_Y / ground_menu->getContentSize().height);
	ground_menu->setPosition(5 * PT_X, 4*PT_Y);
   
	
	int so_sao = logicgame->getStar();
	if (so_sao >= 1 && logicgame->getLevelCanPlay() == logicgame->getLevelPlaying()) logicgame->setLevelCanPlay(logicgame->getLevelPlaying() + 1);
	  logicgame->updateStarOfLevel(so_sao, logicgame->getLevelPlaying());


	std::stringstream ss;
	ss << "Animation" << so_sao;
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Export/sao/sao0.png", "Export/sao/sao0.plist", "Export/sao/sao.ExportJson");
	Armature *armature = Armature::create("sao");
	std::string anim = ss.str();
	armature->setPosition(ccp(5 * PT_X, 9 * PT_Y));
	armature->setScale(4.6 * PT_X / armature->getContentSize().width);
	this->addChild(armature, 2);
	armature->runAction(Sequence::create(MoveTo::create(1, Point(5 * PT_X, 4.1 * PT_Y)), CallFunc::create(CC_CALLBACK_0(LoseLayer::callback2, this, armature,anim)), NULL));
	Menu* pMenu = Menu::create(ground_menu, menu, refresh, next, NULL);
	pMenu->setAnchorPoint(Point(0, 0));
	pMenu->setPosition(0, -pMenu->getContentSize().height);
	this->addChild(pMenu, 1);

	MoveTo *action = MoveTo::create(0.5f, Point(0, 0));
	pMenu->runAction(action);

	Director::getInstance()->getRunningScene()->addChild(this,10);
}
void LoseLayer::callback2(Node *node,std::string anim)
{
	((Armature *)node)->getAnimation()->play(anim);
}
LoseLayer *LoseLayer::init(ProcessLayer *layer)
{
	auto loselayer = new LoseLayer(layer);
	loselayer->autorelease();
	return loselayer;
}
void LoseLayer::refresh(Object* sender)
{
	Director::getInstance()->getScheduler()->resumeTarget(layer);
	layer->refresh(true);
	Director::getInstance()->getRunningScene()->removeChild(this);
}
void LoseLayer::menu(Object *sender)
{
	 Director::getInstance()->replaceScene(MenuScreen::create());
	//Director::getInstance()->replaceScene(TransitionMoveInB::create(1,Option::createScene()));
}
void LoseLayer::next(Object* sender)
{
	float PT_X = logicgame->getPTX();
	float PT_Y = logicgame->getPTY();
	if (logicgame->getLevelPlaying() < logicgame->getLevelCanPlay())
	{
		Director::getInstance()->getRunningScene()->removeAllChildren();
		logicgame->setLevelPlaying(logicgame->getLevelPlaying() + 1);
		Director::getInstance()->getRunningScene()->addChild(ProcessLayer::createLayer(logicgame->getLevelPlaying()));
	}
	else
	{
		log("lose layer");
		ResourceManager *res = ResourceManager::init();
		MenuItemImage *notibackground = MenuItemImage::create(res->get("label_notice","all"), res->get("label_notice","all"));
		_size(notibackground,0, 0.5, 5, 2.5);
		cocos2d::LabelTTF *noti = cocos2d::LabelTTF::create("You must achieve at least one star", "fonts/CFGoliathDemo-Regular.ttf",30, Size(4 * PT_X, 2 * PT_Y));
		noti->setColor(ccc3(0,85,0));
		noti->setPosition(0 * PT_X, 0.1 * PT_Y);
		MenuItemLabel *itemnoti = MenuItemLabel::create(noti);
		Menu *menu = Menu::create();
		menu->setAnchorPoint(Point(0, 0));
		menu->addChild(notibackground);
		menu->addChild(itemnoti, 1);
		this->addChild(menu, 2);
		menu->runAction(Sequence::create(DelayTime::create(2), CallFunc::create(CC_CALLBACK_0(LoseLayer::callback3, this,menu)), NULL));
		//Director::getInstance()->setNotificationNode(noti);
		delete res;
	}
}
void LoseLayer::callback3(Node *node)
{
	this->removeChild(node);
}