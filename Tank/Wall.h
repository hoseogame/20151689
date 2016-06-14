#pragma once
#include "Object.h"

class Wall : public Object
{
private:

public:
	explicit Wall(int x, int y);
	virtual ~Wall();

	bool CollisionCheck(Object* obj) override;
	void DoAction(KEY key) override;
};