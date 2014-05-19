#include "Spy.h"
Spy::Spy(ProcessLayer *layer) :layer(layer)
{
	world = layer->getWorld();
	PT_X = Config::init()->getPTX();
	PT_Y = Config::init()->getPTY();
	v_typeSprite = typeSprite::rect;
	v_bodytype = b2_staticBody;
	v_friction = 0.2f;
	v_restitution = 0.0f;
	v_density = 0.0f;
	v_order = 0;
	v_angle = 0;
	tag = "none";
}

void Spy::setSprite(Sprite *sprite)
{
	this->sprite = sprite;
}
void Spy::setBody(b2Body *body)
{
	this->body = body;
}
Sprite *Spy::getSprite()
{
	return sprite;
}
b2Body *Spy::getBody()
{
	return body;
}


Spy *Spy::filename(const std::string& filename)
{
	v_filename = filename;
	return this;
}
Spy *Spy::x(float x)
{
	v_x = x;
	return this;
}
Spy *Spy::y(float y)
{
	v_y = y;
	return this;
}
Spy *Spy::width(float width)
{
	v_width = width;
	return this;
};
Spy *Spy::height(float height)
{
	v_height = height;
	return this;
}
Spy *Spy::order(float order)
{
	v_order = order;
	return this;
}
Spy *Spy::R(float R)
{
	v_R = R;
	return this;
}
Spy *Spy::type(typeSprite type)
{
	v_typeSprite = type;
	return this;
}
Spy *Spy::density(float density)
{
	v_density = density;
	return this;
}
Spy *Spy::restitution(float restitution)
{
	v_restitution = restitution;
	return this;
}
Spy *Spy::typeBody(b2BodyType typebody)
{
	v_bodytype = typebody;
	return this;
}
Spy *Spy::friction(float friction)
{
	v_friction = friction;
	return this;
}

Spy *Spy::createA()
{
    sprite = Sprite::create(v_filename);
	sprite->setPosition(v_x*PT_X, v_y*PT_Y);
	b2BodyDef bodydef;
	bodydef.position.Set(v_x, v_y);
	bodydef.type = v_bodytype;
	b2FixtureDef fixture;
	if (v_typeSprite == typeSprite::circle)
	{
		sprite->setScale(v_R * 2 * PT_X / sprite->getContentSize().width, v_R * 2 * PT_Y / sprite->getContentSize().height);
		layer->addChild(sprite, v_order);
		b2CircleShape shape;
		shape.m_radius = v_R;
		fixture.shape = &shape;
		fixture.density = v_density;
		fixture.friction = v_friction;
		fixture.restitution = v_restitution;
		body = layer->getWorld()->CreateBody(&bodydef);
		body->CreateFixture(&fixture);
		body->SetUserData(sprite);
		body->SetTransform(b2Vec2(v_x, v_y), v_angle);
	}
	else if (v_typeSprite == typeSprite::rect)
	{
		sprite->setScale(v_width* PT_X / sprite->getContentSize().width, v_height* PT_Y / sprite->getContentSize().height);
		layer->addChild(sprite, v_order);
		b2PolygonShape shape;
		shape.SetAsBox(v_width / 2, v_height / 2);
		fixture.shape = &shape;
		fixture.density = v_density;
		fixture.friction = v_friction;
		fixture.restitution = v_restitution;
		body = layer->getWorld()->CreateBody(&bodydef);
		body->CreateFixture(&fixture);
		body->SetUserData(sprite);
		body->SetTransform(b2Vec2(v_x, v_y), v_angle);
	}
	isPhysic = true;
	return this;
}
Spy *Spy::createS()
{
    sprite = Sprite::create(v_filename);
	sprite->setPosition(v_x*PT_X, v_y*PT_Y);
	if (v_typeSprite == typeSprite::circle)
	{
		sprite->setScale(v_R * 2 * PT_X / sprite->getContentSize().width, v_R * 2 * PT_Y / sprite->getContentSize().height);
	}
	else if (v_typeSprite == typeSprite::rect)
	{
		sprite->setScale(v_width* PT_X / sprite->getContentSize().width, v_height* PT_Y / sprite->getContentSize().height);
	}
	layer->addChild(sprite, v_order);
	sprite->setRotation(v_angle);
	return this;
}
Spy* Spy::createP()
{
	b2BodyDef bodydef;
	bodydef.position.Set(v_x, v_y);
	bodydef.type = v_bodytype;
	b2FixtureDef fixture;
	if (v_typeSprite == typeSprite::circle)
	{
		b2CircleShape shape;
		shape.m_radius = v_R;
		fixture.shape = &shape;
		fixture.density = v_density;
		fixture.friction = v_friction;
		fixture.restitution = v_restitution;
		body = layer->getWorld()->CreateBody(&bodydef);
		body->CreateFixture(&fixture);
		body->SetUserData(sprite);
		body->SetTransform(b2Vec2(v_x, v_y), -CC_DEGREES_TO_RADIANS(v_angle));
	}
	else if (v_typeSprite == typeSprite::rect)
	{
		b2PolygonShape shape;
		shape.SetAsBox(v_width / 2, v_height / 2);
		fixture.shape = &shape;
		fixture.density = v_density;
		fixture.friction = v_friction;
		fixture.restitution = v_restitution;
		body = layer->getWorld()->CreateBody(&bodydef);
		body->CreateFixture(&fixture);
		body->SetUserData(sprite);
		body->SetTransform(b2Vec2(v_x, v_y), -CC_DEGREES_TO_RADIANS(v_angle));
	}
	isPhysic = true;
	return this;
}
Spy *Spy::notify()
{
	if (isPhysic)
	{
		world->SetAllowSleeping(false);
		body->SetTransform(b2Vec2(v_x, v_y), v_angle);
		body->SetLinearVelocity(b2Vec2(0, 0));
		body->SetAngularVelocity(0);
		world->SetAllowSleeping(true);
	}
	else
	{
		sprite->setPosition(v_x*PT_X, v_y*PT_Y);
		if (v_typeSprite == typeSprite::circle)
		{
			sprite->setScale(v_R * 2 * PT_X / sprite->getContentSize().width, v_R * 2 * PT_Y / sprite->getContentSize().height);
		}
		else if (v_typeSprite == typeSprite::rect)
		{
			sprite->setScale(v_width* PT_X / sprite->getContentSize().width, v_height* PT_Y / sprite->getContentSize().height);
		}
		sprite->setRotation(v_angle);
	}
	
	return this;
}

Spy* Spy::rotate(float angle)
{
	v_angle = angle;
	return this;
}

void Spy::destroy()
{
	layer->removeChild(sprite);
	world->DestroyBody(body);
	isDestroyed = true;
}
void Spy::recreate()
{
	if (isPhysic)
	{
		this->createA();
	}
	else
	{
		this->createS();
	}
	isDestroyed = false;
}
void Spy::setPhysic(bool checked)
{
	this->isPhysic = checked;
}
bool Spy::getPhysic()
{
	return this->isPhysic;
}
Spy::~Spy()
{
	
}
Spy* Spy::setTag(char *tag_in)
{
	tag = tag_in;
	return this;
}
char* Spy::getTag()
{
	return tag;
}
void Spy::setIsDestroyed(bool isDestroyed)
{
	this->isDestroyed = isDestroyed;
}
bool Spy::getIsDestroyed()
{
	return this->isDestroyed;
}
void Spy::setWillDestroyed(bool des)
{
	this->willDestroyed = des;
}
bool Spy::getWillDestroyed()
{
	return this->willDestroyed;
}