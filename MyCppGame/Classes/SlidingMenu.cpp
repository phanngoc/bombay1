#include "SlidingMenu.h"

SlidingMenuGrid::SlidingMenuGrid(){
}

SlidingMenuGrid::~SlidingMenuGrid(){
	log("Grid Destructor");
}

void SlidingMenuGrid::onExit(){
	_eventDispatcher->removeEventListener(touchListener);
    log("Grid onExit");
}

bool SlidingMenuGrid::init(){
	if ( !CCLayer::init() ){
		return false;
	}
	return true;
}

SlidingMenuGrid* SlidingMenuGrid::menuWithArray(CCArray *items, int cols, int rows, CCPoint pos,Point pad,Point border){
	return menuWithArray(items,cols,rows,pos,pad,border,false);
}


SlidingMenuGrid* SlidingMenuGrid::menuWithArray(CCArray *items, int cols, int rows, CCPoint pos, CCPoint pad,Point border,bool vertical){
	SlidingMenuGrid *slidingMenu = new SlidingMenuGrid();
	if (slidingMenu && slidingMenu->initWithArray(items ,cols ,rows ,pos ,pad ,border,vertical)){
		slidingMenu->autorelease();
		return slidingMenu;
	}
	CC_SAFE_DELETE(slidingMenu);
	return NULL;
}

bool SlidingMenuGrid::initWithArray(CCArray *items, int cols, int rows, Point pos, Point pad,Point border_t, bool vertical){
	if( !CCLayer::init() ){
		return false;
	}
    
     //default threshold Values
	if (vertical)
		threshold = Director::getInstance()->getVisibleSize().height / 4;
    else 
		threshold = Director::getInstance()->getVisibleSize().width / 4;


	selectedItem = NULL;
	setTouchEnabled(true);
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SlidingMenuGrid::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SlidingMenuGrid::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SlidingMenuGrid::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(SlidingMenuGrid::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithFixedPriority(touchListener, 2);
	pMenu=Menu::create();
	pMenu->setPosition(pos);
	addChild(pMenu,0);
    
    CCObject *object;
    CCMenuItemSprite *getItem;
    
    CCARRAY_FOREACH(items, object){
        getItem = (CCMenuItemSprite*)object;
        pMenu->addChild(getItem, 1, getItem->getTag());
    }
	border = border_t;
	padding = pad;
	iCurrentPage = 0;
	bMoving = false;
	iMenuRows=rows;
	menuOrigin = pos;
	fMoveDeadZone = 10;
	bVerticalPaging = vertical;
	fAnimSpeed = 1;
	state=kCCMenuStateWaiting;
	(bVerticalPaging) ? this->buildGridVertical(cols ,rows) : this->buildGrid(cols, rows);
	//this->setPosition(menuOrigin);
	return true;
}

void SlidingMenuGrid::buildGrid(int cols, int rows){
	Size winSize = Director::getInstance()->getVisibleSize();
	float x_start;
	if (cols % 2 == 0)
	{
		x_start = cols / 2*padding.x-padding.x/2;
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
	int col = 0, row = 0;
	Vector<Node*> child = pMenu->getChildren();
	//Point position=getPosition();
	iPageCount=0;
	for(auto item : child){
		MenuItemSprite* getItem = (MenuItemSprite*) item;
		getItem->setPosition(ccp(-x_start + col * padding.x + (iPageCount * winSize.width), y_start - row * padding.y));
		getItem->setScale((padding.x-border.x) / getItem->getContentSize().width, (padding.y-border.y) / getItem->getContentSize().height);
		++col;
		if (col == cols){
			col = 0;
			++row;
			if( row == rows ){
				iPageCount++;
				col = 0;
				row = 0;
			}
		}
		
	}
	if(child.size() > rows*cols*iPageCount){//   <-- add code for FIX (Mr.  K pop)
		iPageCount++;
	}
}



void SlidingMenuGrid::buildGridVertical(int cols, int rows){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	int col = 0, row = 0;
	Vector<Node*> child = pMenu->getChildren();
	CCPoint position=getPosition();
	iPageCount=0;
	for(auto item : child){
		CCMenuItemSprite* getItem = (CCMenuItemSprite*) item;
		getItem->setPosition(ccp(position.x + menuOrigin.x+col * padding.x , position.y +(winSize.height-menuOrigin.y)- row * padding.y - (iPageCount * winSize.height)));
		++col;
		if (col == cols){
			col = 0;
			++row;
			if( row == rows ){
				iPageCount++;
				col = 0;
				row = 0;
			}
		}
        
	}
	if(child.size() > rows*cols*iPageCount){ //   <-- add code for FIX (Mr.  K pop)
		iPageCount++;
	}
}


CCMenuItemSprite* SlidingMenuGrid::GetItemWithinTouch(Touch* touch){
    CCPoint touchLocation = touch->getLocation();
    
	// Parse our menu items and see if our touch exists within one.
	Vector<Node*> child = pMenu->getChildren();
	for(auto item : child){
		
		CCMenuItemSprite * getItem= static_cast<CCMenuItemSprite *>(item);
        
		CCPoint local = getItem->convertToNodeSpace(touchLocation);
		CCRect r = getItem->rect();
		r.origin = CCPointZero;// If the touch was within this item. Return the item.
		if (r.containsPoint(local)){
			return getItem;
		}
	}
	// Didn't touch an item.
	return NULL;
}

bool SlidingMenuGrid::onTouchBegan(CCTouch* touch, CCEvent* event){
	touchOrigin = touch->getLocation();

	// If we weren't in "waiting" state bail out.
	if (state == kCCMenuStateWaiting){
		// Activate the menu item if we are touching one.
		if (!bMoving){
			selectedItem = GetItemWithinTouch(touch);
			if (selectedItem){
				if (selectedItem->isEnabled())
					selectedItem->selected();
			}
		}
		state = kCCMenuStateTrackingTouch;
	}
	return true;
}

void SlidingMenuGrid::onTouchCancelled(CCTouch* touch, CCEvent* event){
	if(selectedItem){
		selectedItem->unselected();
		selectedItem = NULL;
		state = kCCMenuStateWaiting;
	}
}

void SlidingMenuGrid::onTouchMoved(CCTouch* touch, CCEvent* event){
	if(GetItemWithinTouch(touch) == NULL && selectedItem){
		//Touch Cancelled
		if(selectedItem->isEnabled()){
			selectedItem->unselected();
		}
		selectedItem = NULL;
		state = kCCMenuStateWaiting;
		return;
	}
    
	if(GetItemWithinTouch(touch) != NULL && selectedItem){
		return;
	}
	// Calculate the current touch point during the move.
    touchStop = touch->getLocation();// Distance between the origin of the touch and current touch point.
	fMoveDelta = (bVerticalPaging) ? (touchStop.y - touchOrigin.y) : (touchStop.x - touchOrigin.x);// Set our position.
	
	if(iCurrentPage == 0){
        if (fMoveDelta < threshold) {
            setPosition(GetPositionOfCurrentPageWithOffset(fMoveDelta));
            bMoving = true;
            return;
        }
    }
    else if(iCurrentPage == iPageCount - 1){
        if (fMoveDelta > -threshold) {
            setPosition(GetPositionOfCurrentPageWithOffset(fMoveDelta));
            bMoving = true;
            return;
        }
    }
    else{
        setPosition(GetPositionOfCurrentPageWithOffset(fMoveDelta));
        bMoving = true;
    }
}

void SlidingMenuGrid::onTouchEnded(CCTouch* touch, CCEvent* event){
	if( bMoving ){
		bMoving = false;
		{
			// Do we have multiple pages?
			if( iPageCount > 1 && (fMoveDeadZone < abs(fMoveDelta))){
				// Are we going forward or backward?
				bool bForward = (fMoveDelta > 0) ? true : false;
				
				// Do we have a page available?
				if(bVerticalPaging){
					if(bForward && (iPageCount>iCurrentPage+1)){
						// Increment currently active page.
						iCurrentPage++;
					}
					else if(!bForward && (iCurrentPage > 0)){
						// Decrement currently active page.
						iCurrentPage--;
					}
				}
				else{
					if(!bForward && (iPageCount>iCurrentPage+1)){
						// Increment currently active page.
						iCurrentPage++;
					}
					else if(bForward && (iCurrentPage > 0)){
						// Decrement currently active page.
						iCurrentPage--;
					}
				}
				
				// Start sliding towards the current page.
				moveToCurrentPage();
			}
			else{
				if(selectedItem){
					selectedItem->unselected();
					selectedItem->activate();
				}
                moveToCurrentPage();
			}
		}
	}
	else{
		if(selectedItem){
			if(selectedItem->isEnabled()){
				selectedItem->unselected();
				selectedItem->activate();
			}
		}
	}
	state = kCCMenuStateWaiting;
}

void SlidingMenuGrid::moveToCurrentPage(bool animated){
    if (animated){
		MoveTo* action = MoveTo::create(fAnimSpeed*0.3f, GetPositionOfCurrentPage());
        runAction(action);
    }
    else{
        setPosition(GetPositionOfCurrentPage());
    }
}

CCPoint SlidingMenuGrid::GetPositionOfCurrentPage(){
	CCSize winSize = CCDirector::getInstance()->getVisibleSize();
	CCPoint position=getPosition();
	if(bVerticalPaging)
		position=Point(0,iCurrentPage*winSize.height);
	else
		position = Point(-(iCurrentPage)*winSize.width, 0);
	return position;
}

CCPoint SlidingMenuGrid::GetPositionOfCurrentPageWithOffset(float offset){
	CCPoint position=GetPositionOfCurrentPage();
	if(bVerticalPaging)
		position.y+=offset;
	else
		position.x+=offset;
	return position;
}

// Returns the swiping dead zone.
float SlidingMenuGrid::GetSwipeDeadZone(){
	return fMoveDeadZone;
}

//Sets the width limit for First/Last page swipe limit.
void SlidingMenuGrid::setThresholdPageLimit(float fValue){
    threshold = fValue;
}

void SlidingMenuGrid::SetSwipeDeadZone(float fValue){
	fMoveDeadZone = fValue;
}

// Returns wheather or not vertical paging is enabled.
bool SlidingMenuGrid::IsVerticallyPaged(){
	return bVerticalPaging;
}

// Sets the vertical paging flag.
void SlidingMenuGrid::SetVerticalPaging(bool bValue){
	bVerticalPaging = bValue;
	// this->buildGridVertical();
}

void SlidingMenuGrid::gotoPage(int iPage, bool animated){
	int iSetPage=iPage;
	if(iPage<=0)
		iSetPage=1;
	else if(iPage>iPageCount){
		iSetPage=iPageCount;
	}
	iCurrentPage=iSetPage-1;
	moveToCurrentPage(animated);
}

void SlidingMenuGrid::setPageLabel( int iPage,CCNode * pLabel){
	addChild(pLabel,10);
	if(!pLabel)
		return;
	int iSetPage=iPage;
	if(iPage<=0)
		iSetPage=1;
	else if(iPage>iPageCount){
		iSetPage=iPageCount;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize labelSize= pLabel->getContentSize();
	CCPoint pt=getPosition();
	if(bVerticalPaging)
		pt=CCPointMake(menuOrigin.x+labelSize.width/2,winSize.height-menuOrigin.y-winSize.height*(iSetPage-1)-iMenuRows*padding.y-labelSize.height/2);
	else
		pt=CCPointMake(menuOrigin.x+(iSetPage-1)*winSize.width+labelSize.width/2,winSize.height-menuOrigin.y-iMenuRows*padding.y-labelSize.height/2);
	pLabel->setPosition(pt);
}