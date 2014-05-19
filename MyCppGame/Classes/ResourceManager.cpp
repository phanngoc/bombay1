#include "ResourceManager.h"
using namespace std;

ResourceManager::ResourceManager(char *tag)
{
	current_tag = tag;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "logicgame.db";
	int rc;
	rc = sqlite3_open(path.c_str(), &db);
	if (rc){
		log("Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else{
		log("Opened database successfully\n");
	}

}
ResourceManager::ResourceManager()
{
	current_tag = "none";
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "logicgame.db";
	int rc;
	rc = sqlite3_open(path.c_str(), &db);
	if (rc){
		log("Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else{
		log("Opened database successfully\n");
	}

}

void ResourceManager::setTag(char *tag)
{
	current_tag = tag;
}
char *ResourceManager::get(char *name)
{
	std::string str(name);
	stringstream stream;
	stream << "select resource.url from resource, tag where resource.name = '"
		+ str + "' and resource.tag_id = tag.id and tag.name = '" + current_tag + "'";
	string temp_str = stream.str();
	const char *sql = temp_str.c_str();

	int rc;
	sqlite3_stmt *stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	char * result = (char *)malloc(100);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		strcpy(result,(char *)sqlite3_column_text(stmt, 0));
		break;
	}
	sqlite3_finalize(stmt);
	return result;
}

const char *ResourceManager::get(char *name,char *tag)
{
	std::string str(name);
	stringstream stream;
	stream << "select resource.url from resource, tag where resource.name = '"
		+ str + "' and resource.tag_id = tag.id and tag.name = '" + tag + "'";
	string temp_str = stream.str();
	const char *sql = temp_str.c_str();

	int rc;
	sqlite3_stmt *stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	char * result = (char *)malloc(100);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		strcpy(result, (char *)sqlite3_column_text(stmt, 0));
		break;
	}
	sqlite3_finalize(stmt);
	return result;
}
ResourceManager* ResourceManager::init(char* tag)
{
	ResourceManager *res = new ResourceManager(tag);
	log("init ResourceManager");
	return res;
}
ResourceManager* ResourceManager::init()
{
	ResourceManager *res = new ResourceManager();
	log("init ResourceManager");
	return res;
}
ResourceManager::~ResourceManager()
{
	log("destroy ResourceManager");
	sqlite3_close(db);
}
