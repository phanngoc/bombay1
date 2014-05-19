#include "Level1.h"
Level1::Level1(ProcessLayer *layer) :layer(layer)
{
	PT_X = logicgame->getPTX();
	PT_Y = logicgame->getPTY();
	spymanager = layer->getSpyManager();
	world = layer->getWorld();
}
void Level1::create_level()
{
	ResourceManager *res = ResourceManager::init("level1");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite *ground = Sprite::create(res->get("ground"));
	ground->setPosition(5 * PT_X, 0.25f*PT_Y);
	ground->setScale(visibleSize.width / ground->getContentSize().width, 0.5 * PT_X / ground->getContentSize().height);
	layer->addChild(ground, -1);
	/*set up cho background*/
	Sprite *background = Sprite::create(res->get("background_top"));
	background->setPosition(Point(0, 0.5 * PT_Y));
	background->setAnchorPoint(Point(0, 0));
	background->setScale(visibleSize.width / background->getContentSize().width, (visibleSize.height - 0.5 * PT_Y) / background->getContentSize().height);
	layer->addChild(background, -1);

	res->setTag("all");
	//*Set up cho dai bac*
	spymanager->createSpy()->filename(res->get("daibac"))->x(9)->y(0.8)->width(1)->height(1)->createA();
	//*Set up cho cac vat the*
	//spy->createPolygon("thanh/thanhda.png", 6.5, 4.5, 1, 0.3, fixt);
	//*vat the thanh duoi*
	res->setTag("level1");
	spymanager->createSpy()->filename(res->get("thanh_da"))->x(9)->y(5.1)->width(2)->height(0.2)->createA();

	//*2 thanh chon*
	spymanager->createSpy()->filename(res->get("bar_wood"))
		->x(8.5)->y(5.6)->width(0.2)->height(0.75)->typeBody(b2_dynamicBody)->density(0.2)->createA();
	spymanager->createSpy()->filename(res->get("bar_wood"))
		->x(9.3)->y(5.6)->width(0.2)->height(0.75)->typeBody(b2_dynamicBody)->density(0.2)->createA();
	//*thanh ben tren*
	spymanager->createSpy()->filename(res->get("bar_wood_top"))
		->x(8.9)->y(6.0)->width(1.2)->height(0.1)->typeBody(b2_dynamicBody)->density(0.2)->createA();
	//* tao con heo :D*
	spymanager->createSpy()->filename(res->get("goal"))->x(8.9)->y(6.3)->R(0.25)->density(0.5)->restitution(0.2)->friction(0.7)->typeBody(b2_dynamicBody)->type(typeSprite::circle)->createA()->setTag("goal");
	//*tao dan la chim*
	spymanager->createSpy()->filename(res->get("dan"))->R(0.25)->type(typeSprite::circle)->x(8.25)->y(1.5)->createS()->setTag("dan");



	//*tao neo de thanh da quay*
	b2Body *bodyneo = spymanager->createSpy()->filename(res->get("neo"))->x(2)->y(4)->R(0.1)->typeBody(b2_staticBody)->type(typeSprite::circle)->createA()->setTag("neo")->getBody();
	//*tao thanh quay*
	b2Body *bodythanhrotate = spymanager->createSpy()->filename(res->get("thanh_rang"))
		->x(2)->y(4)->width(2)->height(0.2)->typeBody(b2_dynamicBody)->setTag("thanh_rang")
		->density(0.5f)->createA()->getBody();
	//*noi neo va thanh quay*
	b2RevoluteJointDef def;
	def.collideConnected = false;
	def.bodyA = bodyneo;
	def.bodyB = bodythanhrotate;
	def.enableMotor = true;
	def.maxMotorTorque = 20;
	def.motorSpeed = CC_DEGREES_TO_RADIANS(90);
	def.localAnchorA.Set(0, 0);
	def.localAnchorB.Set(0, 0);
	b2RevoluteJoint *revolutejoint = (b2RevoluteJoint*)world->CreateJoint(&def);

	ArmatureDataManager::getInstance()->addArmatureFileInfo("Export/may/may0.png", "Export/may/may0.plist", "Export/may/may.ExportJson");
	Armature *armature = Armature::create("may");
	armature->getAnimation()->playWithIndex(0);
	armature->setScale(0.5f);
	armature->setPosition(ccp(4 * PT_X, 6.2 * PT_Y));
	layer->addChild(armature, 2);

	logicgame->setCountMonster(1);
	logicgame->setLevelPlaying(1);
}
void Level1::contact_level(b2Contact* contact)
{

}
void Level1::update(float dt)
{

}
void Level1::refresh()
{
	b2RevoluteJointDef def;
	def.collideConnected = false;
	def.bodyA = spymanager->getChildByTag("neo")->getBody();
	def.bodyB = spymanager->getChildByTag("thanh_rang")->getBody();
	def.enableMotor = true;
	def.maxMotorTorque = 20;
	def.motorSpeed = CC_DEGREES_TO_RADIANS(90);
	def.localAnchorA.Set(0, 0);
	def.localAnchorB.Set(0, 0);
	b2RevoluteJoint *revolutejoint = (b2RevoluteJoint*)world->CreateJoint(&def);
}