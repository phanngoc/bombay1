#include "LogicGame.h"


using namespace std;

inline bool file_exists(const std::string& name) 
{
	ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	}
	else {
		f.close();
		return false;
	}
}
inline bool file_exists_1(const std::string& name) {
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
LogicGame::LogicGame()
{
	log("instance logicgame");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	PT_X = visibleSize.width / 10;
	PT_Y = visibleSize.height / 7.5;
	count_monster = 0;
	count_monster_is_killed = 0;
	levelplaying = 1;
	levelcanplay = UserDefault::getInstance()->getIntegerForKey("levelcanplay", 3);

	FileUtils* fileUtils = FileUtils::getInstance();
	std::string from = fileUtils->fullPathForFilename("logicgame.db");
	fflush(stdout);
	std::string path = fileUtils->getWritablePath();
	path += "logicgame.db";
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
	//	if (!file_exists(path))
	//	{
			log("win 32:file chua ton tai");
			std::ifstream  src(from, ifstream::binary);
			std::ofstream  dst(path, ofstream::binary);
			dst << src.rdbuf();
			src.close();
			dst.close();
	//	}
	}
	else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
	//	if (!file_exists(path))
	//	{
			Data data = fileUtils->getDataFromFile(from.c_str());
			std::fstream ofs;
			ofs.open(path, std::fstream::out);
			ofs.write((char*)data.getBytes(), data.getSize());
			ofs.close();
	//	}
	}

}
LogicGame::~LogicGame()
{

}
float LogicGame::getPTX()
{
	return PT_X;
}
float LogicGame::getPTY()
{
	return PT_Y;
}
void LogicGame::loadDatabase()
{
	std::string path = FileUtils::getInstance()->getWritablePath() += "logicgame.db";
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	void* data = this;
	

	rc = sqlite3_open(path.c_str(), &db);
	if (rc){
		log("Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else{
		log("Opened database successfully\n");
	}


	sql = "SELECT * from progress";

	rc = sqlite3_exec(db, sql,callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK){
		log("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		log("Operation done successfully\n");
	}
	int check = sqlite3_close(db);
	if (!check)
		log("dong thanh cong");
	
}


std::map<int, int> LogicGame::getProgress()
{
	return progress;
}
void LogicGame::setProgress(int level,int star)
{
	progress[level] = star;
}
void LogicGame::increaseMonsterIsKilled()
{
	this->count_monster_is_killed++;
}
void LogicGame::removeItemChildSpy(Spy* child)
{
	this->childspy.eraseObject(child);
}
void LogicGame::setChildSpy(Vector<Spy*>childspy)
{
	this->childspy = childspy;
}
void LogicGame::setCountMonster(int count)
{
	count_monster = count;
}
void LogicGame::setLevelPlaying(int level)
{
	this->levelplaying = level;
}
int LogicGame::getLevelPlaying()
{
	return levelplaying;
}

void LogicGame::setMonsterIsKilled(int monster)
{
	this->count_monster_is_killed = monster;
}
int LogicGame::getStar()
{
	float radio = (float)((float)count_monster_is_killed /(float)count_monster);
	if (radio <= 0.1)
	{
		return 0;
	}
	else if (radio < 0.34)
	{
		return 1;
	}
	else if (radio <= 0.67)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}
int LogicGame::getLevelCanPlay()
{
	return levelcanplay;
}
void LogicGame::refreshMonsterIsKilled()
{
	this->count_monster_is_killed = 0;
}
void LogicGame::setLevelCanPlay(int level)
{
	this->levelcanplay = level;
	UserDefault::getInstance()->setIntegerForKey("levelcanplay", level);
}
void LogicGame::updateStarOfLevel(int star, int level)
{	
	if (star > progress[level])
	{
		progress[level] = star;
		std::string path = FileUtils::getInstance()->getWritablePath() += "logicgame.db";

		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		char *sql="";

		rc = sqlite3_open(path.c_str(), &db);
		if (rc){
			log("Can't open database: %s\n", sqlite3_errmsg(db));
			exit(0);
		}
		else{
			log("Opened database successfully\n");
		}
		stringstream strs;
		strs << "update progress set count_star= " << star << " where level= "<<level;
		string temp_str = strs.str();

		rc = sqlite3_exec(db, (const char*)temp_str.c_str(), NULL, NULL, &zErrMsg);
		if (rc != SQLITE_OK){
			log("SQL error: %s\n|%d", zErrMsg,rc);
			sqlite3_free(zErrMsg);
		}
		else{
			log("Operation done successfully\n");
		}

		sqlite3_close(db);
	}
}