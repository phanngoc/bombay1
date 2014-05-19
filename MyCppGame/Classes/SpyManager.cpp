#include "SpyManager.h"
SpyManager::SpyManager(ProcessLayer *layer) :layer(layer)
{
	PT_X = Config::init()->getPTX();
	PT_Y = Config::init()->getPTY();
	childspy = new Vector<Spy*>;
}
Spy *SpyManager::createSpy()
{
	Spy *spy = new Spy(layer);
	this->setChildSpy(spy);
	return spy;
}
void SpyManager::setChildSpy(Spy* child)
{
	childspy->pushBack(child);
}
Vector<Spy*>*SpyManager::getChildSpy()
{
	return childspy;
}
Spy* SpyManager::getChildByTag(char *tag)
{
	for (int i = 0; i < childspy->size(); i++)
	{
		auto child = childspy->at(i);
		if (child->getTag() == tag)
		{
			return child;
		}
	}
	return nullptr;
}
Spy *SpyManager::getChildByBody(b2Body *body)
{
	for (int i = 0; i < childspy->size(); i++)
	{
		auto child = childspy->at(i);
		if (child->getBody() == body)
		{
			return child;
		}
	}
	return nullptr;
}
Vector<Spy*> SpyManager::getManyChildByTag(char *tag)
{
	Vector<Spy*> spys ;
	for (int i = 0; i < childspy->size(); i++)
	{
		auto child = childspy->at(i);
		if (child->getTag() == tag)
		{
			spys.pushBack(child);
		}
	}
	return spys;
}
Sprite* SpyManager::createSprite(const std::string& filename, float x, float y, float width, float height, int order)
{
	Sprite *sprite = Sprite::create(filename);
	sprite->setPosition(x*PT_X, y*PT_Y);
	sprite->setScale(width* PT_X / sprite->getContentSize().width, height * PT_Y / sprite->getContentSize().height);
	layer->addChild(sprite, order);
	return sprite;
}