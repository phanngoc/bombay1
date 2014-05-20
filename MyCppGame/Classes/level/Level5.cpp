#include "Level5.h"
Level5::Level5(ProcessLayer *layer) :layer(layer)
{
	PT_X = logicgame->getPTX();
	PT_Y = logicgame->getPTY();
	spymanager = layer->getSpyManager();
	world = layer->getWorld();
}
void Level5::create_level()
{
	ResourceManager *res = ResourceManager::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite *ground = Sprite::create(res->get("ground", "level1"));
	ground->setPosition(5 * PT_X, 0.25f*PT_Y);
	ground->setScale(visibleSize.width / ground->getContentSize().width, 0.5 * PT_X / ground->getContentSize().height);
	layer->addChild(ground, -1);
	/*set up cho background*/
	Sprite *background = Sprite::create(res->get("background_top", "level1"));
	background->setPosition(Point(0, 0.5 * PT_Y));
	background->setAnchorPoint(Point(0, 0));
	background->setScale(visibleSize.width / background->getContentSize().width, (visibleSize.height - 0.5 * PT_Y) / background->getContentSize().height);
	layer->addChild(background, -1);
	spymanager->createSpy()->filename(res->get("dan", "level1"))->R(0.25)->type(typeSprite::circle)->x(8.25)->y(1.5)->createS()->setTag("dan");
	//*Set up cho dai bac*
	spymanager->createSpy()->filename(res->get("daibac","all"))->x(9)->y(0.8)->width(1)->height(1)->createA();

	spymanager->createSpy()->filename(res->get("bar_wood_bot", "level5"))->x(5)->y(5.0625)->width(1)->height(0.125)->createA();
	spymanager->createSpy()->filename(res->get("wood_square", "level4"))->x(5)->y(5.375)->width(0.5)->height(0.5)->typeBody(b2_dynamicBody)->createA();
	spymanager->createSpy()->filename(res->get("pig_cold", "level4"))->x(5)->y(5.875)->R(0.25)->typeBody(b2_dynamicBody)->type(typeSprite::circle)->density(0.5)->createA()->setTag("goal");

	
	spymanager->createSpy()->filename(res->get("bar_wood_bot", "level5"))->x(3.5)->y(2.5625)->width(1)->height(0.125)->createA();
	spymanager->createSpy()->filename(res->get("wood_square", "level4"))->x(3.5)->y(2.875)->width(0.5)->height(0.5)->typeBody(b2_dynamicBody)->createA();
	spymanager->createSpy()->filename(res->get("pig_cold", "level4"))->x(3.5)->y(3.375)->R(0.25)->typeBody(b2_dynamicBody)->type(typeSprite::circle)->density(0.5)->createA()->setTag("goal");

	spymanager->createSpy()->filename(res->get("bar_wood_bot", "level5"))->x(7.5)->y(2.5625)->width(1)->height(0.125)->createA();
	spymanager->createSpy()->filename(res->get("wood_square", "level4"))->x(7.5)->y(2.875)->width(0.5)->height(0.5)->typeBody(b2_dynamicBody)->createA();
	spymanager->createSpy()->filename(res->get("pig_cold", "level4"))->x(7.5)->y(3.375)->R(0.25)->typeBody(b2_dynamicBody)->type(typeSprite::circle)->density(0.5)->createA()->setTag("goal");
	logicgame->setCountMonster(3);
	delete res;
}
void Level5::refresh()
{

}
void Level5::update(float dt)
{

}
void Level5::contact_level(b2Contact*)
{

}