#include "ControlLevel.h"
#include "ResourceManager.h"
ControlLevel::ControlLevel(int level, ProcessLayer* processlayer) :level(level), layer(processlayer)
{
	logicgame->refreshMonsterIsKilled();
	logicgame->setLevelPlaying(level);
	switch (level)
	{
	 case 1: clevel = new Level1(processlayer); break;
	 case 2: clevel = new Level2(processlayer); break;
	 case 3: clevel = new Level3(processlayer); break;
	 case 4: clevel = new Level4(processlayer); break;
	 case 5: clevel = new Level5(processlayer); break;
	 case 6: clevel = new Level6(processlayer); break;
	}
	clevel->create_level();
}
ControlLevel::~ControlLevel()
{
	delete clevel;
}
ControlLevel *ControlLevel::init(int level, ProcessLayer* processlayer)
{
	return new ControlLevel(level, processlayer);
}

void ControlLevel::initContact(b2Contact *contact)
{
	clevel->contact_level(contact);
}
void ControlLevel::initUpdate(float dt)
{
	clevel->update(dt);
}
void ControlLevel::refresh()
{
	clevel->refresh();
}
