#include "Level3.h"
Level3::Level3(ProcessLayer *layer) :layer(layer)
{
	PT_X = logicgame->getPTX();
	PT_Y = logicgame->getPTY();
	spymanager = layer->getSpyManager();
	world = layer->getWorld();
}
void Level3::create_level()
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
	//*Tao bong bong'*
	b2Body *bodybubble = spymanager->createSpy()->filename(res->get("bubble", "level3"))->x(2.25)->y(5.4)->width(0.5)->height(0.65)->typeBody(b2_dynamicBody)->density(0.5)->createA()->setTag("bubble")->getBody();
	bodybubble->SetGravityScale(-1);
	//*Tao con pig lien ket voi bong bong tren*
	b2Body *bodypig_1 = spymanager->createSpy()->filename(res->get("goal", "level1"))->x(2.25)->y(4.25)->R(0.25)->density(0.5)->restitution(0.2)->friction(0.7)->typeBody(b2_dynamicBody)->type(typeSprite::circle)->createA()->setTag("goal")->getBody();
	//*Tao cai day noi hai vat tren*
	b2Body *bodyrope_1 = spymanager->createSpy()->filename(res->get("rope", "level3"))->x(2.25)->y(4.75)->width(0.05)->height(1)->density(0.5)->typeBody(b2_dynamicBody)->createA()->setTag("rope")->getBody();
	/*gio noi chung lai bang revolute joint*/
	bodybubble->SetGravityScale(-(bodypig_1->GetMass() + bodyrope_1->GetMass()) / bodybubble->GetMass());
	b2RevoluteJointDef def;
	def.collideConnected = false;
	def.bodyA = bodypig_1;
	def.bodyB = bodyrope_1;
	def.localAnchorA.Set(0, 0.25);
	def.localAnchorB.Set(0, -0.5);
	world->CreateJoint(&def)->SetUserData((void*)"pig_rope");
	def.bodyA = bodybubble;
	def.bodyB = bodyrope_1;
	def.localAnchorA.Set(0, -0.3);
	def.localAnchorB.Set(0, 0.5);
	world->CreateJoint(&def);
	//*Tao qua bong bong thu 2*
	b2Body *bodybubble_2 = spymanager->createSpy()->filename(res->get("bubble", "level3"))->x(6.25)->y(6.375)->width(0.5)->height(0.65)->typeBody(b2_dynamicBody)->density(0.5)->createA()->setTag("bubble")->getBody();
	//*Tao con pig lien ket voi bong bong tren*
	b2Body *bodypig_2 = spymanager->createSpy()->filename(res->get("goal", "level1"))->x(6.25)->y(5.25)->R(0.25)->density(0.5)->restitution(0.2)->friction(0.7)->typeBody(b2_dynamicBody)->type(typeSprite::circle)->createA()->setTag("goal")->getBody();
	//*Tao cai day noi hai vat tren*
	b2Body *bodyrope_2 = spymanager->createSpy()->filename(res->get("rope", "level3"))->x(5.75)->y(5.25)->width(0.05)->height(1)->density(0.5)->typeBody(b2_dynamicBody)->createA()->setTag("rope")->getBody();
	/*gio noi chung lai bang revolute joint*/
	bodybubble_2->SetGravityScale(-(bodypig_2->GetMass() + bodyrope_2->GetMass()) / bodybubble_2->GetMass());
	def.collideConnected = false;
	def.bodyA = bodypig_2;
	def.bodyB = bodyrope_2;
	def.localAnchorA.Set(0, 0.25);
	def.localAnchorB.Set(0, -0.5);
	world->CreateJoint(&def)->SetUserData((void*)"pig_rope");

	def.bodyA = bodybubble_2;
	def.bodyB = bodyrope_2;
	def.localAnchorA.Set(0, -0.3);
	def.localAnchorB.Set(0, 0.5);
	world->CreateJoint(&def);

	//*Tao dan*
	spymanager->createSpy()->filename(res->get("dan", "level1"))->R(0.25)->type(typeSprite::circle)->x(8.25)->y(1.5)->createS()->setTag("dan");


	delete res;
	logicgame->setCountMonster(2);
	logicgame->setLevelPlaying(3);

}
void Level3::contact_level(b2Contact* contact)
{
	Spy *spyA = spymanager->getChildByBody(contact->GetFixtureA()->GetBody());
	Spy *spyB = spymanager->getChildByBody(contact->GetFixtureB()->GetBody());
	if (spyA != nullptr && spyB != nullptr)
	{
		if (((spyA->getTag() == "dan") && (spyB->getTag() == "goal")))
		{
			b2JointEdge *joint = spyB->getBody()->GetJointList();
			if (joint != nullptr || joint != NULL)
			{
				b2Joint *joint_e = joint->joint;
				for (; joint_e != NULL; joint_e = joint_e->GetNext())
				{
					if (joint_e->GetUserData() == "pig_rope")
					{
						spyA->getSprite()->runAction(CallFuncN::create(CC_CALLBACK_0(Level3::doCallback, this, joint_e)));
						break;
					}
				}
			}
		}
		if ((spyB->getTag() == "dan") && (spyA->getTag() == "goal"))
		{
			b2JointEdge *joint = spyA->getBody()->GetJointList();
			if (joint != nullptr || joint != NULL)
			{
				b2Joint *joint_e = joint->joint;
				for (; joint_e != NULL; joint_e = joint_e->GetNext())
				{
					if (joint_e->GetUserData() == "pig_rope")
					{
						spyB->getSprite()->runAction(CallFuncN::create(CC_CALLBACK_0(Level3::doCallback, this, joint_e)));
						break;
					}
				}
			}
		}
	}

}
void Level3::doCallback(b2Joint *joint)
{
	world->DestroyJoint(joint);
}
void Level3::update(float dt)
{
	//b2Body *body = spymanager->getChildByTag("bubble")->getBody();
	//body->ApplyForceToCenter(b2Vec2(0,-20*body->GetLinearVelocity().y),true);
}
void Level3::refresh()
{
	Vector<Spy*> goals = spymanager->getManyChildByTag("goal");
	Vector<Spy*> ropes = spymanager->getManyChildByTag("rope");
	for (int i = 0; i < goals.size(); i++)
	{
		b2Body *bodypig = goals.at(i)->getBody();
		b2Body *bodyrope = ropes.at(i)->getBody();
		b2RevoluteJointDef def;
		def.collideConnected = false;
		def.bodyA = bodypig;
		def.bodyB = bodyrope;
		def.localAnchorA.Set(0, 0.25);
		def.localAnchorB.Set(0, -0.5);
		b2RevoluteJoint *revolutejoint = (b2RevoluteJoint*)world->CreateJoint(&def);
		revolutejoint->SetUserData((void*)"pig_rope");
	}
	Vector<Spy*> bubbles = spymanager->getManyChildByTag("bubble");
	for (int i = 0; i < bubbles.size(); i++)
	{
		b2Body *bodybubble = bubbles.at(i)->getBody();
		b2Body *bodyrope = ropes.at(i)->getBody();
		b2RevoluteJointDef def;
		def.collideConnected = false;
		def.bodyA = bodybubble;
		def.bodyB = bodyrope;
		def.localAnchorA.Set(0, -0.3);
		def.localAnchorB.Set(0, 0.5);
		b2RevoluteJoint *revolutejoint = (b2RevoluteJoint*)world->CreateJoint(&def);
	}

}
