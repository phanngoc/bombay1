#include "ControlListener.h"
class MyListener :public b2ContactListener
{
	public:
		MyListener(ProcessLayer *layer) :layer(layer)
		{
			spymanager = layer->getSpyManager();
		};
		void BeginContact(b2Contact* contact)
		{
			b2Body *bodyA = contact->GetFixtureA()->GetBody();
			b2Body *bodyB = contact->GetFixtureB()->GetBody();
			Spy *spyA = spymanager->getChildByBody(bodyA);
			Spy *spyB = spymanager->getChildByBody(bodyB);
			if (bodyA->GetType() == b2_staticBody && 
				  ( (spyA == nullptr)||
				  ( (spyA!=nullptr)&&(spyA->getTag()!="thanh_user") ) 
				  ) )
			{
				if (spyB != nullptr)
				{
					if (spyB->getTag() == "goal")
					{
						if (!spyB->getWillDestroyed())
						{
							logicgame->increaseMonsterIsKilled();
							spyB->setWillDestroyed(true);
							spyB->getSprite()->runAction(Sequence::create(DelayTime::create(1.5), CallFuncN::create(CC_CALLBACK_1(MyListener::doCallback, this, spyB)), NULL));
						}
					}
				}
			}
			if (bodyB->GetType() == b2_staticBody &&
				((spyB == nullptr) ||
				((spyB != nullptr) && (spyB->getTag() != "thanh_user"))
				))
			{
				if (spyA != nullptr)
				{
					if (spyA->getTag() == "goal")
					{
						if (!spyA->getWillDestroyed())
						{
							logicgame->increaseMonsterIsKilled();
							spyA->setWillDestroyed(true);
							spyA->getSprite()->runAction(Sequence::create(DelayTime::create(1.5), CallFuncN::create(CC_CALLBACK_1(MyListener::doCallback, this, spyA)), NULL));
						}
					}
				}
			}
			layer->getControlLevel()->initContact(contact);
		}
		void doCallback(Node *node, Spy*res_spy)
		{
			if (res_spy->getWillDestroyed())
			{
				res_spy->destroy();
			}
		}
	private :
		ProcessLayer *layer;
		SpyManager *spymanager;

};

ControlListener::ControlListener(ProcessLayer* processlayer) :layer(processlayer)
{
	spymanager = layer->getSpyManager();
	layer->getWorld()->SetContactListener(new MyListener(layer));
}

