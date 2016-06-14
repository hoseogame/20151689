#pragma once
#include "Object.h"

class Boss : public Object
{
private:

public:
	explicit Boss(int x, int y);
	virtual ~Boss();

	bool CollisionCheck(Object* obj) override;
	void DoAction(KEY key) override;
};