#include "WrapSlidingMenu.h"
#include "Config.h"
#include "ResourceManager.h"
WrapSlidingMenu* WrapSlidingMenu::menuWithArray(CCArray *items, int cols, int rows, CCPoint pos, CCPoint pad, Point border,Sprite *menu_prev,Sprite *menu_next)
{
	WrapSlidingMenu *slidingMenu = new WrapSlidingMenu();
	slidingMenu->setControl(menu_prev, menu_next);
	if (slidingMenu && slidingMenu->initWithArray(items, cols, rows, pos, pad, border, false)){
		slidingMenu->autorelease();
		return slidingMenu;
	}
	CC_SAFE_DELETE(slidingMenu);
	return NULL;
}
void WrapSlidingMenu::buildGrid(int cols, int rows){
	float PT_X = Config::init()->getPTX();
	float PT_Y = Config::init()->getPTY();
	log("WrapSlidingMenu::buildGrid");
	ResourceManager *res = ResourceManager::init("all");

	Size winSize = Director::getInstance()->getVisibleSize();
	float x_start;
	if (cols % 2 == 0)
	{
		x_start = cols / 2 * padding.x - padding.x / 2;
	}
	else{
		x_start = floor(cols / 2)*padding.x;
	}
	float y_start;
	if (rows % 2 == 0)
	{
		y_start = rows / 2 * padding.y - padding.y / 2;
	}
	else{
		y_start = floor(rows / 2)*padding.y;
	}

	std::map<int, int> progress = logicgame->getProgress();
	int levelcanplay = logicgame->getLevelCanPlay();
	

	int col = 0, row = 0;
	Vector<Node*> child = pMenu->getChildren();
	iPageCount = 0;
	for (int i = 0; i < child.size();i++){
		auto item = child.at(i);
		MenuItemSprite* getItem = (MenuItemSprite*)item;
		getItem->setPosition(ccp(-x_start + col * padding.x + (iPageCount * winSize.width), y_start - row * padding.y));
		float scale_X = (padding.x - border.x) / getItem->getContentSize().width;
		float scale_Y = (padding.y - border.y) / getItem->getContentSize().height;
		getItem->setScale(scale_X,scale_Y);
		++col;
		if (col == cols){
			col = 0;
			++row;
			if (row == rows){
				iPageCount++;
				col = 0;
				row = 0;
			}
		}
		if (i + 1 <= levelcanplay)
		{
			std::stringstream ss;
			ss << (i + 1);
			std::string str = ss.str();
			cocos2d::LabelTTF *number = cocos2d::LabelTTF::create(str, "fonts/WHITRABT.TTF", 35, Size(0, 0), kCCTextAlignmentCenter);
			number->setPosition(0.7*PT_X/scale_X,0.9*PT_Y/scale_Y);
			number->setColor(ccc3(0, 0, 97));
			getItem->addChild(number,10);

			if (progress[i + 1] < 1) goto sao_0;
			auto sao = Sprite::create(res->get("sao_level"));
			sao->setScale(0.375 * PT_X / sao->getContentSize().width / scale_X, 0.375 * PT_Y / sao->getContentSize().height / scale_Y);
			sao->setPosition(0.35*PT_X/scale_X,0.25*PT_Y/scale_Y);
			getItem->addChild(sao);

			if (progress[i + 1] < 2) goto sao_0;
			auto sao1 = Sprite::create(res->get("sao_level"));
			sao1->setScale(0.375*PT_X / sao1->getContentSize().width / scale_X, 0.375 * PT_Y / sao1->getContentSize().height / scale_Y);
			sao1->setPosition(0.7 * PT_X/scale_X, 0.25*PT_Y/scale_Y);
			getItem->addChild(sao1);

			if (progress[i + 1] < 3) goto sao_0;
			auto sao2 = Sprite::create(res->get("sao_level"));
			sao2->setScale(0.375*PT_X / sao2->getContentSize().width / scale_X, 0.375 * PT_Y / sao2->getContentSize().height / scale_Y);
			sao2->setPosition(1.05 * PT_X / scale_X, 0.25*PT_Y / scale_Y);
			getItem->addChild(sao2);

		}
		sao_0:
		continue;
	}//End for
	if (child.size() > rows*cols*iPageCount){//   <-- add code for FIX (Mr.  K pop)
		iPageCount++;
	}
	
	delete res;
}

bool WrapSlidingMenu::onTouchBegan(CCTouch* touch, CCEvent* event)
{
	Point point = touch->getLocation();
	
	if (menu_prev->getBoundingBox().containsPoint(point))
	{
		if (iCurrentPage > 0)
		{
			iCurrentPage -= 1;
			moveToCurrentPage(true);
		}
		return true;
	}
	if (menu_next->getBoundingBox().containsPoint(point))
	{
		if (iCurrentPage < iPageCount-1)
		{
			iCurrentPage += 1;
			moveToCurrentPage(true);
		}
		return true;
	}
	
	SlidingMenuGrid::onTouchBegan(touch, event);
	return true;
}
void WrapSlidingMenu::setControl(Sprite *menu_prev, Sprite *menu_next)
{
	this->menu_prev = menu_prev;
	this->menu_next = menu_next;
}