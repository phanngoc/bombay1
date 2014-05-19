#ifndef LOGIC_GAME_H
#define LOGIC_GAME_H
#include "cocos2d.h"
#include "Spy.h"
#include <vector>
#include <map>

#include <iostream>   
#include <fstream> 
#include "CCPlatformMacros.h"

#include <istream>
#include <iostream>
#include <fstream>
#include <iterator>

class Spy;
USING_NS_CC;
class LogicGame{
	public:
		LogicGame();
		~LogicGame();
		void loadDatabase();
		void setCountMonster(int);
		void setMonsterIsKilled(int);
		void increaseMonsterIsKilled();
		void refreshMonsterIsKilled();
		int getStar();
		int getLevelCanPlay();
		void setLevelCanPlay(int);
		void setChildSpy(Vector<Spy*>);
		void removeItemChildSpy(Spy*);
		void setProgress(int,int);
		std::map<int, int> getProgress();
		void setLevelPlaying(int);
		int getLevelPlaying();
		void updateStarOfLevel(int, int);
		float getPTX();
		float getPTY();
		static int callback(void *data, int argc, char **argv, char **azColName){
				((LogicGame*)data)->setProgress(atoi(argv[2]),atoi(argv[1]));
			return 0;
		}
	private:
		int count_monster;
		int levelplaying;
		int levelcanplay=1;
		int count_monster_is_killed;
		Vector<Spy*> childspy;
		std::map<int, int> progress;
		float PT_X;
		float PT_Y;
};
#endif
