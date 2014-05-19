#include "Level4.h"
Level4::Level4(ProcessLayer *layer) :layer(layer)
{
	PT_X = logicgame->getPTX();
	PT_Y = logicgame->getPTY();
	spymanager = layer->getSpyManager();
	world = layer->getWorld();
}
void Level4::create_level()
{
	ResourceManager *res = ResourceManager::init("level4");
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
	spymanager->createSpy()->filename(res->get("dan", "level1"))->R(0.25)->type(typeSprite::circle)->x(8.25)->y(1.5)->createS()->setTag("dan");
	spymanager->createSpy()->filename(res->get("bar_wood", "level4"))->x(4.5)->y(2.0625)->width(2)->height(0.125)->density(2)->createA();
	spymanager->createSpy()->filename(res->get("wood_square", "level4"))->x(4.5)->y(2.5)->width(0.5)->height(0.5)->density(1)->typeBody(b2_dynamicBody)->createA();
	spymanager->createSpy()->filename(res->get("pig_cold", "level4"))->x(4.5)->y(3.01)->R(0.25)->typeBody(b2_dynamicBody)->type(typeSprite::circle)->density(0.5)->createA()->setTag("goal");
	b2Body *bodypig_1 = spymanager->createSpy()->filename(res->get("goal", "level1"))->x(3)->y(4)->R(0.25)->density(0.5)->restitution(0.2)->friction(0.7)->typeBody(b2_dynamicBody)->type(typeSprite::circle)->createA()->setTag("goal")->getBody();
	b2Body *bodypig_2 = spymanager->createSpy()->filename(res->get("goal", "level1"))->x(6)->y(4)->R(0.25)->density(0.5)->restitution(0.2)->friction(0.7)->typeBody(b2_dynamicBody)->type(typeSprite::circle)->createA()->setTag("goal")->getBody();
	b2PulleyJointDef def;
	def.Initialize(bodypig_1, bodypig_2, b2Vec2(3, 6), b2Vec2(6, 6), bodypig_1->GetWorldCenter(), bodypig_2->GetWorldCenter(), 1.0f);
	world->CreateJoint(&def);
	doCallback(0);
	delete res;
	logicgame->setCountMonster(3);
	logicgame->setLevelPlaying(4);
}
void Level4::contact_level(b2Contact *contact)
{
	b2Body *bodyA = contact->GetFixtureA()->GetBody();
	b2Body *bodyB = contact->GetFixtureB()->GetBody();
	Spy *spyA = spymanager->getChildByBody(bodyA);
	Spy *spyB = spymanager->getChildByBody(bodyB);
	if (spyA != nullptr)
	{
		if (spyA->getWillDestroyed())
		{
			check_loop_change_mass = 0;
		}
	}
	if (spyB != nullptr)
	{
		if (spyB->getWillDestroyed())
		{
			check_loop_change_mass = 0;
		}
	}
}
void Level4::update(float dt)
{

}
void Level4::changeMass(b2Body *body, float mas)
{
	b2MassData massData;
	body->GetMassData(&massData);
	float scaleFactor = mas / massData.mass;
	massData.mass *= scaleFactor;
	massData.I *= scaleFactor;
	body->SetMassData(&massData);
}
void Level4::doCallback(int swap)
{
	if (!check_loop_change_mass)
		return;
	dem++;
	log("doCallback:%d", dem);
	Vector<Spy*> goals = spymanager->getManyChildByTag("goal");
	b2Body *bodypig_1 = goals.at(1)->getBody();
	b2Body *bodypig_2 = goals.at(2)->getBody();
	if (swap == 0)
	{
		changeMass(bodypig_1, 0.2);
		changeMass(bodypig_2, 0.09);
		swap = 1;
	}
	else
	{
		changeMass(bodypig_2, 0.2);
		changeMass(bodypig_1, 0.09);
		swap = 0;
	}
	Action *action = Sequence::create(DelayTime::create(2), CallFuncN::create(CC_CALLBACK_0(Level4::doCallback, this, swap)), NULL);
	action->setTag(3);
	layer->runAction(action);
}
void Level4::refresh()
{
	layer->stopAllActions();
	check_loop_change_mass = 1;
	Vector<Spy*> goals = spymanager->getManyChildByTag("goal");
	b2PulleyJointDef def;
	b2Body *bodypig_1 = goals.at(1)->getBody();
	b2Body *bodypig_2 = goals.at(2)->getBody();
	def.Initialize(bodypig_1, bodypig_2, b2Vec2(3, 6), b2Vec2(6, 6), bodypig_1->GetWorldCenter(), bodypig_2->GetWorldCenter(), 1.0f);
	world->CreateJoint(&def);
	doCallback(0);
}