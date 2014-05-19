#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include "cocos2d.h"
#include "lib/sqlite3.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <iterator>
USING_NS_CC;

class ResourceManager {
	public:
		ResourceManager(char*);
		ResourceManager();
		~ResourceManager();
		static ResourceManager* init(char*);
		static ResourceManager* init();
	    char *get(char *);
		const char *get(char *, char *);
		void setTag(char *);

	private:
		char * current_tag = NULL;
		sqlite3 *db;
};
#endif
