#include "LayerMenuLevel.h"

bool LayerMenuLevel::init()
{

	ResourceManager *res = ResourceManager::init("all");
	
	float PT_X = Config::init()->getPTX();
	float PT_Y = Config::init()->getPTY();
	Size winsize = Director::getInstance()->getVisibleSize();
	Sprite *background_level = Sprite::create(res->get("background_menu_level"));
	background_level->setScale(winsize.width / background_level->getContentSize().width, winsize.height / background_level->getContentSize().height);
	background_level->setAnchorPoint(Point(0, 0));
	background_level->setPosition(0, 0);
	this->addChild(background_level, -1);
	MenuItemImage *back = MenuItemImage::create(res->get("back_menu_level"), res->get("back_menu_level"), res->get("back_menu_level"), CC_CALLBACK_0(LayerMenuLevel::backCallback, this));
	_size(back, 0.875-5, 0.625-3.75, 1.75, 1.25);
	Menu *menu = Menu::create();
	menu->addChild(back);
	this->addChild(menu, 0);
	std::map<int, int> progress = logicgame->getProgress();
	CCArray* array = CCArray::createWithCapacity(10);
	int levelcanplay = logicgame->getLevelCanPlay();
	for (int i = 0; i < 15; i++){
		
		Sprite *sprite;
		if (i + 1>levelcanplay)
		{
			sprite = Sprite::create(res->get("item_menu_lock"));
		}
		else
		{
			sprite = Sprite::create(res->get("item_menu_unlock"));
		}
		
		MenuItemSprite *menuItem = MenuItemSprite::create(sprite, sprite, sprite, CC_CALLBACK_1(LayerMenuLevel::gridClickedCallBack, this,i));
		
		menuItem->setTag(i+1);
		array->addObject(menuItem);
	}
	auto control_layer = Layer::create();
	Sprite *menu_prev = Sprite::create(res->get("menu_prev"));
	menu_prev->setScale(1 * PT_X / menu_prev->getContentSize().width, 1.25*PT_Y / menu_prev->getContentSize().height);
	menu_prev->setPosition(1.2*PT_X, 6.5*PT_Y);
	control_layer->addChild(menu_prev, 10);
	Sprite* menu_next = Sprite::create(res->get("menu_next"));
	menu_next->setScale(1 * PT_X / menu_next->getContentSize().width, 1.25*PT_Y / menu_next->getContentSize().height);
	menu_next->setPosition(8.8*PT_X, 6.5*PT_Y);
	control_layer->addChild(menu_next, 10);
	this->addChild(control_layer, 10);
	//This is how we create grid:
	delete res;
	WrapSlidingMenu *grid = WrapSlidingMenu::menuWithArray(array, 3, 3, CCPoint(5 * PT_X, 3.2 * PT_Y), CCPoint(2 * PT_X, 2 * PT_Y), Point(0.6*PT_X, 0.4*PT_Y), menu_prev,menu_next);

	grid->SetSwipeDeadZone(1*PT_X);
	grid->setTag(0);
	this->addChild(grid);
	return true;
}
void LayerMenuLevel::backCallback()
{
	Director::getInstance()->replaceScene(MainScreen::create());
}
void LayerMenuLevel::gridClickedCallBack(Ref *sender,int i)
{
	MenuItemSprite * node = static_cast<MenuItemSprite*>(sender);
	logicgame->setLevelPlaying(node->getTag());
	if (logicgame->getLevelCanPlay() >= node->getTag())
	{
		Director::getInstance()->replaceScene(Process::create());
	}
	
}
LayerMenuLevel::~LayerMenuLevel()
{
	log("Destructor layermenulevel");
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}