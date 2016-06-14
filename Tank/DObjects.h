#pragma once
#include <time.h>

enum GAME_STATE { DoINIT, DoREADY, DoRUNNING, DoSUCCESS, DoFAILED, DoSTOP, DoRESULT };
enum DUDAGI_STATE { DoSETUP, DoUP, DoDOWN };

class STAGE_INFO
{
public:
	int nCatchDudagi;
	clock_t LimitTime;
	clock_t UpLimitTime;
	clock_t DownLimitTime;
};

class MANGCHI
{
public:
	int	nIsAttack;
	clock_t	StartTime;
	clock_t	DelayTime;
	int	nIndex;
	int	nStayX, nStayY;
};

class DUDAGI
{
public:
	DUDAGI_STATE nState;
	clock_t   StayTime;
	clock_t	OutPutTime;
	clock_t	OldTime;
};

class XY
{
public:
	int nX, nY;
};
