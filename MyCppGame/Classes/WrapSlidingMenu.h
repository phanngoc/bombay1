#ifndef  WRAP_SLIDING_MENU_H
#define	 WRAP_SLIDING_MENU_H
#include "cocos2d.h"
#include "SlidingMenu.h"
#include "LogicGame.h"
class LogicGame;
extern LogicGame *logicgame;
class WrapSlidingMenu : public SlidingMenuGrid{
	public:
		void buildGrid(int cols, int rows);
		static WrapSlidingMenu* menuWithArray(CCArray *items, int cols, int rows, CCPoint pos, CCPoint pad, Point border,Sprite *menu_prev,Sprite *menu_next);
		bool onTouchBegan(CCTouch* touch, CCEvent* event);
		void setControl(Sprite *, Sprite *);
	private:
		Sprite *menu_prev;
		Sprite *menu_next;

};
#endif