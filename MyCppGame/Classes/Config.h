#ifndef CONFIG_H
#define CONFIG_H
#include "cocos2d.h"
USING_NS_CC;
class Config :public Ref{
	public:
		static Config *init();
		float getPTX();
		float getPTY();
		void setPTX(float);
		void setPTY(float);
	private:
		float PT_X;
		float PT_Y;
};
#endif