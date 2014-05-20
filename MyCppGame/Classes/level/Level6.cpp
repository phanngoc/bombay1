#include "Level6.h"
Level6::Level6(ProcessLayer *layer) :layer(layer)
{
	PT_X = logicgame->getPTX();
	PT_Y = logicgame->getPTY();
	spymanager = layer->getSpyManager();
	world = layer->getWorld();
}
void Level6::create_level()
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
	spymanager->createSpy()->filename(res->get("daibac", "all"))->x(9)->y(0.8)->width(1)->height(1)->createA();
	spymanager->createSpy()->filename(res->get("bar_wood_vertical_long", "level6"))->x(3.875)->y(2.5)->width(0.25)->height(5)->typeBody(b2_dynamicBody)->createA();

	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("pattern1.png");
	Vector2dVector polygonPoints;
	polygonPoints.push_back(Vector2d(100, 100));
	polygonPoints.push_back(Vector2d(200, 100));
	polygonPoints.push_back(Vector2d(300, 200));

	PRFilledPolygon *filledPolygon = PRFilledPolygon::filledPolygonWithPointsAndTexture(polygonPoints, texture);
	filledPolygon->setPosition(Point(200, 200));
	layer->addChild(filledPolygon, 12);
	logicgame->setCountMonster(2);
	delete res;
}
void Level6::refresh()
{

}
void Level6::update(float dt)
{

}
void Level6::contact_level(b2Contact*)
{

}