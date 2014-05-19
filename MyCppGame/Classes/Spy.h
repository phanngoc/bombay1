#ifndef SPY_H
#define SPY_H
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "ProcessLayer.h"
#include <vector>

enum typeSprite{ rect, circle, polygon };
class ProcessLayer;
class Spy :public Object{
	public:
		Spy(ProcessLayer*);
		~Spy();

		Sprite *getSprite();
		b2Body *getBody();
		void setSprite(Sprite *sprite);
		void setBody(b2Body *body);
		bool getPhysic();
		void setPhysic(bool checked);
		bool getIsDestroyed();
		void setIsDestroyed(bool);
		bool getWillDestroyed();
		void setWillDestroyed(bool);
		/*-----------------*/
		Spy *filename(const std::string& filename);
		Spy *x(float x);
		Spy *y(float y);
		Spy *width(float width);
		Spy *height(float height);
		Spy *order(float order);
		Spy *R(float R);
		Spy *type(typeSprite);
		Spy *density(float density);
		Spy *restitution(float restitution);
		Spy *typeBody(b2BodyType);
		Spy *friction(float friction);
		Spy *rotate(float angle);
		Spy *createA();
		Spy *createS();
		Spy *createP();
		Spy *notify();

		void destroy();
		void recreate();
		Spy* setTag(char*);
		char* getTag();

		/*-----------------*/

	protected :
		/*------------*/
		float v_x;
		float v_y;
		std::string v_filename;
		float v_width;
		float v_height;
		float v_order;
		float v_R;
		b2BodyType v_bodytype;
		float v_density;
		float v_friction;
		float v_restitution;
		typeSprite v_typeSprite;
		float v_angle;
		/*------------*/

		ProcessLayer *layer;
		b2World *world;
		Sprite *sprite;
		b2Body *body;
		float PT_X;
		float PT_Y;
		bool isPhysic = false;
		char *tag;
		bool isDestroyed = false;
		bool willDestroyed = false;
};
#endif
