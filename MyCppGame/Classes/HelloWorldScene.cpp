#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    //
	PT_X = Director::getInstance()->getVisibleSize().width / 10;
	//PT_Y = Director::getInstance()->getVisibleSize().height / 15;
	PT_Y = PT_X;


	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);


	b2BodyDef backgroundef;
	backgroundef.position.Set(0, 0);
	b2Body *body = world->CreateBody(&backgroundef);


	b2Vec2 bottomLeft;
	bottomLeft.Set(0, 0);
	b2Vec2 bottomRight;
	bottomRight.Set(10, 0);
	b2Vec2 topLeft;
	topLeft.Set(0, 7.5);
	b2Vec2 topRight;
	topRight.Set(10, 7.5);

	b2EdgeShape bottomshape;
	bottomshape.Set(bottomLeft, bottomRight);
	body->CreateFixture(&bottomshape, 0);
	b2EdgeShape leftshape;
	leftshape.Set(bottomLeft, topLeft);
	body->CreateFixture(&leftshape, 0);
	b2EdgeShape rightshape;
	rightshape.Set(bottomRight, topRight);
	body->CreateFixture(&rightshape, 0);
	b2EdgeShape topshape;
	topshape.Set(topLeft, topRight);
	body->CreateFixture(&topshape, 0);
	//body and fixture defs - the common parts
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2FixtureDef fixtureDef;
	fixtureDef.density = 2.0f;
	
	//two shapes
	b2PolygonShape boxShape;
	boxShape.SetAsBox(0.25, 0.25);
	//make box a little to the left
	bodyDef.position.Set(1, 0.5);
	fixtureDef.shape = &boxShape;
	m_bodyA = world->CreateBody(&bodyDef);
	m_bodyA->CreateFixture(&fixtureDef);
	Sprite *spriteA = Sprite::create("nam.png");
	spriteA->setScale(0.5 * PT_X / spriteA->getContentSize().width, 0.5 * PT_Y / spriteA->getContentSize().height);
	this->addChild(spriteA);
	m_bodyA->SetUserData(spriteA);

	

	//and circle a little to the right

	b2CircleShape circleShape;
	circleShape.m_radius = 0.125f;
	bodyDef.position.Set(2, 0.5f);
	fixtureDef.shape = &circleShape;
	b2Body *m_bodyB = world->CreateBody(&bodyDef);
	m_bodyB->CreateFixture(&fixtureDef);
	Sprite *spriteB = Sprite::create("fire.png");
	spriteB->setScale(0.25 * PT_X / spriteB->getContentSize().width, 0.25 * PT_Y / spriteB->getContentSize().height);
	this->addChild(spriteB);
	m_bodyB->SetUserData(spriteB);

	//-----------------------------------------
	//hinh C la thanh
	b2PolygonShape boxShapeC;
	boxShapeC.SetAsBox(1, 0.5);
	//make box a little to the left
	bodyDef.position.Set(3, 0.5);
	fixtureDef.shape = &boxShapeC;
	b2Body *m_bodyC = world->CreateBody(&bodyDef);
	m_bodyC->CreateFixture(&fixtureDef);
	Sprite *spriteC = Sprite::create("thanhmario1.png");
	spriteC->setScale(2 * PT_X / spriteC->getContentSize().width, 1 * PT_Y / spriteC->getContentSize().height);
	this->addChild(spriteC);
	m_bodyC->SetUserData(spriteC);
	//-----------------------------------------
	
	/*
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = m_bodyA;
	revoluteJointDef.bodyB = m_bodyC;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(-2, 0);//the top right corner of the box
	revoluteJointDef.localAnchorB.Set(0, 0);//center of the circle
	//revoluteJointDef.enableLimit = true;
	//revoluteJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(-45);
	//revoluteJointDef.upperAngle = CC_DEGREES_TO_RADIANS(45);
	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 5;
	revoluteJointDef.motorSpeed = CC_DEGREES_TO_RADIANS(90); //1 turn per second counter-clockwise

	b2RevoluteJoint* m_joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
	*/
	//---------------------------------------------------------------------------------
	float x = 5;
	float y = 7.0f;
	b2BodyDef bodyDef1;
	bodyDef1.type = b2BodyType::b2_staticBody;
	bodyDef1.position.Set(x, y);
	b2Body *body1 = world->CreateBody(&bodyDef1);
	b2Body *prevBody = body1;
	b2Body *bodyrope;
	for (int i = 1; i <= 10; i++)
	{
		Sprite *sprite = Sprite::create("squareblue.png");
		sprite->setScale(0.05*PT_X / sprite->getContentSize().width, 0.05*PT_Y / sprite->getContentSize().height);
		this->addChild(sprite);
		float newX = x;
		float newY = y - i * 0.05;
		b2BodyDef bodyDefThanh;
		
		bodyDefThanh.type = b2BodyType::b2_dynamicBody;
		bodyDefThanh.position.Set(newX, newY);
		bodyrope = world->CreateBody(&bodyDefThanh);
		b2PolygonShape shaperope;
		shaperope.SetAsBox(0.025f, 0.025f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shaperope;
		fixtureDef.density = 2.0f;
		//fixtureDef.friction = 1;
		//fixtureDef.restitution = 0.3;
		bodyrope->CreateFixture(&fixtureDef);
		bodyrope->SetUserData(sprite);
		b2DistanceJointDef    rDef;
		rDef.Initialize(prevBody, bodyrope, b2Vec2(0, -0.025), b2Vec2(0, 0.025));
		rDef.dampingRatio = 1;
		rDef.frequencyHz = 30;
		rDef.length = 1;
		rDef.collideConnected = true;
		b2DistanceJoint  * grumoRopeJoint = (b2DistanceJoint  *)world->CreateJoint(&rDef);
		//Wheel join


		
		prevBody = bodyrope;
	}
	/*b2DistanceJointDef def;
	def.bodyA = m_bodyA;
	def.bodyB = m_bodyC;
	def.localAnchorA = b2Vec2(0, 0);
	def.localAnchorB = b2Vec2(0, 1.0f);
	//	def.Initialize(prevBody, body, b2Vec2(0, -0.2f), b2Vec2(0, 0.2f));
	def.length = 2.0f;
	def.dampingRatio = 0.5;
	def.frequencyHz = 0.9;
	def.collideConnected = false;
	b2DistanceJoint *joint = (b2DistanceJoint*)world->CreateJoint(&def);
	*/
	

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(touchListener, 1);

	this->schedule(schedule_selector(HelloWorld::update), 1.0f / 60.0f);
    return true;
}
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("Da touch");
	Sprite *spriteA = (Sprite*)m_bodyA->GetUserData();
	if (spriteA->getPosition().x < touch->getLocation().x)
	{
		m_bodyA->ApplyLinearImpulse(b2Vec2(0.5, 2), m_bodyA->GetWorldCenter(), true);
	}
	else
	{
		m_bodyA->ApplyLinearImpulse(b2Vec2(-0.5 ,2), m_bodyA->GetWorldCenter(), true);
	}
	
	
	return true;
}
void HelloWorld::update(float dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/

	int velocityIterations = 8;
	int positionIterations = 3;

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
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
