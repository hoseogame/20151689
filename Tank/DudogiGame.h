#pragma once
#include <time.h>
#include"DObjects.h"

class DudogiGame
{
private:
	GAME_STATE	m_nGameState;
	int         m_nIsSuccess;
	int			m_nStage;
	int			m_nGrade; // Á¡¼ö 
	int			m_nStageCount;
	int			m_nDudagiCount;
	clock_t		m_GameStartTime, m_UpdateOldTime, m_RemainTime;
	int			m_nTotalGrade;
	XY	m_Point[9];
	DUDAGI	m_Dudagi[9];
	MANGCHI	m_Mangchi;
	STAGE_INFO m_StageInfo[3];
private:
	void Init();
	void Update();
	void Render();
	void Release();
private:
	void Mangchi(int x, int y);
	void MangchiReady(int x, int y);
	void InitScreen();
	void ReadyScreen();
	void SuccessScreen();
	void RunningScreen();
	void FailureScreen();
	void ResultScreen();
public:
	DudogiGame();
	void Run();
};