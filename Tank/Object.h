#pragma once
#include <string>
#include "Input.h"

typedef std::string Shape;

struct Postion
{
public:
	int x;
	int y;
public:
	Postion(int _x, int _y) :
		x(_x),
		y(_y)
	{}

	inline void SetPotion(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

enum ObjectType{
	PLAYER = 0,
	BULLET,
	ENEMY,
	WALL,
	BOX,
	BOSS
};

enum DIRECTION 
{
	UP, DOWN, LEFT, RIGHT, NONE
};

class Object
{
private:
	Postion pos;
	Postion beforePos;
	Shape form;
	ObjectType type;

public:
	Object(int _x, int _y, Shape _form, ObjectType _type);
	virtual ~Object();

	virtual bool CollisionCheck(Object* obj) = 0;
	virtual void DoAction(KEY key) = 0;

	void DrawThis();
	
	inline Postion GetBeforePos()
	{
		return beforePos;
	}

	inline void SetBeforPos(Postion _pos)
	{
		beforePos = _pos;
	}

	inline void SetShape(Shape _form)
	{
		form = _form;
	}

	inline Shape GetShape()
	{
		return form;
	}

	inline void SetPotion(int _x, int _y)
	{
		pos.x = _x;
		pos.y = _y;
	}

	inline Postion GetPotion()
	{
		return pos;
	}
	
	inline ObjectType GetType()
	{
		return type;
	}
};