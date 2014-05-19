#include "ProcessLayer.h"

b2World* ProcessLayer::getWorld()
{
	return world;
}


ProcessLayer *ProcessLayer::createLayer(int level)
{
	ProcessLayer *layer = new ProcessLayer;
	layer->initBackground();
	layer->autorelease();
	ControlLevel *control = ControlLevel::init(level, layer);
	layer->setControlLevel(control);
	return layer;
}
void ProcessLayer::initBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	PT_X = Config::init()->getPTX();
	PT_Y = Config::init()->getPTY();

	spymanager = new SpyManager(this);
	spymanager->retain();
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	ControlListener *listener = new ControlListener(this);

	b2BodyDef backgroundef;
	backgroundef.position.Set(0, 0);
	b2Body *body = world->CreateBody(&backgroundef);


	b2Vec2 bottomLeft;
	bottomLeft.Set(0, 0.5);
	b2Vec2 bottomRight;
	bottomRight.Set(10, 0.5);
	b2Vec2 topLeft;
	topLeft.Set(0, 7.5);
	b2Vec2 topRight;
	topRight.Set(10, 7.5);
	b2EdgeShape bottomshape;
	bottomshape.Set(bottomLeft, bottomRight);
	b2FixtureDef defix;
	defix.shape = &bottomshape;
	defix.density = 1;
	defix.friction = 1;
	body->CreateFixture(&defix);
	b2EdgeShape leftshape;
	leftshape.Set(bottomLeft, topLeft);
	defix.shape = &leftshape;
	body->CreateFixture(&defix);
	b2EdgeShape rightshape;
	rightshape.Set(bottomRight, topRight);
	defix.shape = &rightshape;
	body->CreateFixture(&defix);
	b2EdgeShape topshape;
	topshape.Set(topLeft, topRight);
	defix.shape = &topshape;
	body->CreateFixture(&defix);

	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(ProcessLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ProcessLayer::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ProcessLayer::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithFixedPriority(touchListener, 1);
	this->schedule(schedule_selector(ProcessLayer::update), 1.0f / 60.0f);
	this->schedule(schedule_selector(ProcessLayer::updateAll), 1.0f / 60.0f);
	//*luu du button_fire de control ban*
	button_fire = spymanager->createSprite("button_fire.png", 1, 6.5, 1, 1, 1);
	button_refresh = spymanager->createSprite("refresh.png", 1, 1, 1, 1, 1);
}
bool ProcessLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (button_refresh->getBoundingBox().containsPoint(touch->getLocation()))
	{
		this->refresh(false);
		return true;
	}
	Rect rect = Rect(button_fire->getBoundingBox());
	if (rect.containsPoint(touch->getLocation()))
	{
		if (check_fire == 1) return true;
		check_fire = 1;
		b2Body *bodydan = spymanager->getChildByTag("dan")->density(1)->typeBody(b2_dynamicBody)->restitution(0.5)->friction(0.7)->createP()->getBody();
		bodydan->SetGravityScale(0.5);
		b2Vec2 vect;
		vect.Set(-2.5, 3);
		bodydan->ApplyLinearImpulse(vect, bodydan->GetWorldCenter(), true);
		runAction(Sequence::create(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(ProcessLayer::startCheck,this)), NULL));
		
	}
	else
	{
		spy_temp = spymanager->createSpy()->filename("thanh/thanh_user.png")->x(touch->getLocation().x / PT_X)->y(touch->getLocation().y / PT_Y)
			->order(1)->width(0.2)->height(0.2)->createS()->setTag("thanh_user");
	}

	return true;
}
void ProcessLayer::startCheck()
{
	this->schedule(schedule_selector(ProcessLayer::updateCheck), 1.0f / 60.0f);
}
void ProcessLayer::refresh(bool isAdded)
{
	
 repeat:
	for (int i = 0; i < this->spymanager->getChildSpy()->size(); i++)
	{
		auto child = this->spymanager->getChildSpy()->at(i);
		child->setWillDestroyed(false);
		if (child->getTag() == "thanh_user")
		{
			this->removeChild(child->getSprite());
			world->DestroyBody(child->getBody());
			spymanager->getChildSpy()->eraseObject(child);
			goto repeat;
		}
		else if (child->getTag() == "dan")
		{
			if (child->getPhysic())
			{
				world->DestroyBody(child->getBody());
			}
			child->setPhysic(false);
			child->notify();
		}
		else 
		{
			if (child->getIsDestroyed() == false)
			{
				child->notify();
			}
			else
			{
				child->recreate();
			}
		}

	}
	begin:
	b2Joint *join = world->GetJointList();
	if (join != NULL)
	{
		for (; join != NULL; join = join->GetNext())
		{
			world->DestroyJoint(join);
			goto begin;
		}
	}
	controlLevel->refresh();
	check_fire = 0;
	if (touchListener->checkAvailable() && isAdded)
	{
		log("touch avaible");
		_eventDispatcher->addEventListenerWithFixedPriority(touchListener, 2);
	}
	logicgame->refreshMonsterIsKilled();
	this->unschedule(schedule_selector(ProcessLayer::updateCheck));
}
void ProcessLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (spy_temp == nullptr) return;
	if (check_move) {
		Point drag_start = touch->getStartLocation();
		Point drag_end = touch->getLocation();
		float x_center = (drag_start.x + drag_end.x) / 2 / PT_X;
		float y_center = (drag_start.y + drag_end.y) / 2 / PT_Y;
		float dx = abs(drag_end.x - drag_start.x) / PT_X;
		float dy = abs(drag_end.y - drag_start.y) / PT_Y;
		float dx_ang = (drag_end.x - drag_start.x) / PT_X;
		float dy_ang = (drag_end.y - drag_start.y) / PT_Y;
		float width = sqrt(dx*dx + dy*dy);
		float angle = atan2f(-dy_ang, dx_ang);
		spy_temp->x(x_center)->y(y_center)->width(width)->rotate(CC_RADIANS_TO_DEGREES(angle))->notify();
		spy_temp->density(4)->restitution(0.9)->createP();
	}
	else{
		spy_temp->density(4)->createP();
	}
	check_move = 0;
	spy_temp = nullptr;
}
void ProcessLayer::onTouchesMoved(Touch *touch, Event *unused_event)
{
	check_move = 1;
	if (spy_temp == nullptr) return;
	Point drag_start = touch->getStartLocation();
	Point drag_end = touch->getLocation();
	Vector<Spy*> *childspys = spymanager->getChildSpy();
	for (int i = 0; i < childspys->size(); i++)
	{
		Spy* child = childspys->at(i);
		Sprite *sprite = child->getSprite();
		if (sprite->getBoundingBox().containsPoint(drag_end)&&child->getTag()!="thanh_user")
		{
			spymanager->getChildSpy()->eraseObject(spy_temp);
			this->removeChild(spy_temp->getSprite());
			spy_temp = nullptr;
			return;
		}
	}


	float x_center = (drag_start.x + drag_end.x) / 2 / PT_X;
	float y_center = (drag_start.y + drag_end.y) / 2 / PT_Y;
	float dx = abs(drag_end.x - drag_start.x) / PT_X;
	float dy = abs(drag_end.y - drag_start.y) / PT_Y;
	float dx_ang = (drag_end.x - drag_start.x) / PT_X;
	float dy_ang = (drag_end.y - drag_start.y) / PT_Y;
	float width = sqrt(dx*dx + dy*dy);
	//*Phai co dau - vi ham rotate cung chieu kim dong ho la duong*
	float angle = atan2f(-dy_ang, dx_ang);
	spy_temp->x(x_center)->y(y_center)->width(width)->rotate(CC_RADIANS_TO_DEGREES(angle))->notify();
}

void ProcessLayer::update(float dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/

	int velocityIterations = 8;
	int positionIterations = 1;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	world->Step(dt, velocityIterations, positionIterations);
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			// Synchronize the AtlasSprites position and rotation with the corresponding body
			CCSprite* myActor = (CCSprite*)b->GetUserData();
			myActor->setPosition(CCPointMake(b->GetPosition().x * PT_X, b->GetPosition().y * PT_Y));
			myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}
void ProcessLayer::onExit()
{
	Node::onExit();
	log("onExit ProcessLayer");
	if (touchListener->checkAvailable())
	{
		_eventDispatcher->removeEventListener(touchListener);
	}
}
ProcessLayer::~ProcessLayer()
{
	spymanager->release();
	delete world;
	log("destroy processlayer");
}
SpyManager* ProcessLayer::getSpyManager()
{
	return spymanager;
}
void ProcessLayer::updateCheck(float dt)
{
	if (spymanager->getChildByTag("dan")->getBody()->GetLinearVelocity().Length() < 0.5f)
	{
		Vector<Spy*> spys = spymanager->getManyChildByTag("goal");
		int count_check = 0;
		for (auto child : spys)
		{
			if (child->getBody()->GetLinearVelocity().Length() < 0.2f||child->getIsDestroyed())
			{
				count_check++;	
			}
		}
		if (count_check == spys.size())
		{
			touchListener->retain();
			Director::getInstance()->getScheduler()->pauseTarget(this);
			_eventDispatcher->removeEventListener(touchListener);
			LoseLayer::init(this);
		}
	}
}
void ProcessLayer::setControlLevel(ControlLevel* control)
{
	controlLevel = control;
}
ControlLevel *ProcessLayer::getControlLevel()
{
	return controlLevel;
}
void ProcessLayer::updateAll(float dt)
{
	controlLevel->initUpdate(dt);
}