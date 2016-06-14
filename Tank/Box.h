#pragma once
#include "Object.h"

class Box : public Object
{
private:

public:
	explicit Box(int x, int y);
	virtual ~Box();

	bool CollisionCheck(Object* obj) override;
	void DoAction(KEY key) override;
};