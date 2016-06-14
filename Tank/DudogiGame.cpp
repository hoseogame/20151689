#include <stdio.h>
#include <conio.h>
#include "DudogiGame.h"
#include "DScreen.h"

DudogiGame::DudogiGame()
{
	m_nGameState = DoINIT;
	m_nIsSuccess = 0;
	m_nStage = -1;
	m_nGrade = 0;
	m_nStageCount = 1;
	m_nDudagiCount = 0;
	m_nTotalGrade = 0;
	m_Point[0] = { 10, 15 };
	m_Point[1] = { 20, 15 };
	m_Point[2] = { 30, 15 };
	m_Point[3] = { 10, 10 };
	m_Point[4] = { 20, 10 };
	m_Point[5] = { 30, 10 };
	m_Point[6] = { 10, 5 };
	m_Point[7] = { 20, 5 };
	m_Point[8] = { 30, 5 };
	m_StageInfo[0] = { 2, 1000 * 10, 6000, 4000 };
	m_StageInfo[1] = { 5, 1000 * 10, 2000, 2000 };
	m_StageInfo[2] = { 50, 1000 * 120, 1000, 1000 };
}

void DudogiGame::Init()
{
	int i;

	if (m_nStage == -1) // 1번만 초기화가 되는 부분에 대한 처리 사항
	{
		m_nStage = 0;
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0] );
	}

	m_nDudagiCount = 0; // 잡은 두더지 개수	
	m_nGrade = 0;

	// Note: 망치 셋업
	m_Mangchi.nIsAttack = 0;
	m_Mangchi.nIndex = 0;
	m_Mangchi.nStayX = 38;
	m_Mangchi.nStayY = 10;
	m_Mangchi.StartTime = m_GameStartTime;
	m_Mangchi.DelayTime = 300;

	for (i = 0; i < 9; i++)
	{
		m_Dudagi[i].StayTime = rand() % m_StageInfo[m_nStage].DownLimitTime + 10; // Note: 최소 10은 된다.
		m_Dudagi[i].OldTime = clock();
		m_Dudagi[i].nState = DoSETUP;
		m_Dudagi[i].OutPutTime = rand() % m_StageInfo[m_nStage].UpLimitTime + 10; //최소 10은 된다.
	}
}
void DudogiGame::Update()
{
	int i;
	clock_t CurTime = clock();

	switch (m_nGameState)
	{
	case DoREADY:
		if (CurTime - m_UpdateOldTime > 2000)  // 2초
		{
			m_nGameState = DoRUNNING;
			m_GameStartTime = CurTime;
		}
		break;
	case DoRUNNING:
		if ((CurTime - m_GameStartTime) > m_StageInfo[m_nStage].LimitTime)
		{
			m_nGameState = DoSTOP;
			return;
		}
		else {
			// 두더지 업데이트	
			for (i = 0; i < 9; i++)
			{
				switch (m_Dudagi[i].nState)
				{
				case DoSETUP:
					m_Dudagi[i].OldTime = CurTime;
					m_Dudagi[i].OutPutTime = rand() % (int)m_StageInfo[m_nStage].UpLimitTime + 10;
					m_Dudagi[i].StayTime = rand() % (int)m_StageInfo[m_nStage].DownLimitTime + 10;
					m_Dudagi[i].nState = DoUP;
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3] ); // 나올때만 출력
					break;

				case DoUP:
					if (CurTime - m_Dudagi[i].OldTime > m_Dudagi[i].OutPutTime)
					{
						m_Dudagi[i].OldTime = CurTime;
						m_Dudagi[i].nState = DoDOWN;
					}
					break;

				case DoDOWN:
					if (CurTime - m_Dudagi[i].OldTime > m_Dudagi[i].StayTime)
						m_Dudagi[i].nState = DoSETUP;
					break;

				}
			}

			// 망치 업데이트 
			if (m_Mangchi.nIsAttack)
			{
				// 충돌 테스트 망치는 오직 하나의 두더지만 잡을 수 있기에 하나만 잡았으면 충돌 체크를 빠져 나온다.
				for (i = 0; i < 9; i++)
				{
					if (m_Dudagi[i].nState == DoUP && i == m_Mangchi.nIndex)
					{
						m_nGrade += 10;
						m_nDudagiCount++;
						m_Dudagi[i].nState = DoDOWN; // 죽었으면 다운 상태로 바로 전환을 하도록 한다.															
												   //FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4] );								
						break;
					}
				}

				// Note: 망치의 상태를 변경해주는 부분 망치로 쳤을 때에 일정한 시간 동안 머물도록 하기 위한 부분
				if (CurTime - m_Mangchi.StartTime > m_Mangchi.DelayTime)
				{
					m_Mangchi.nIsAttack = 0;
				}
			}

			m_RemainTime = (m_StageInfo[m_nStage].LimitTime - (CurTime - m_GameStartTime)) / 3000; // 게임 진행 남은 시간
		}
		break;
	case DoSTOP:
		// 성공이냐 실패를 판단해주어서 출력을 해주는 부분이 와야 한다.
		if (m_nDudagiCount >= m_StageInfo[m_nStage].nCatchDudagi)
		{
			m_UpdateOldTime = CurTime;
			m_nGameState = DoSUCCESS;
			m_nTotalGrade += m_nGrade;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6] ); // 미션 성공 사운드
		}
		else {
			m_nGameState = DoFAILED;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1] ); // 미션 실패 사운드
		}
		break;
	case DoSUCCESS:
		if (CurTime - m_UpdateOldTime > 3000)
		{
			m_UpdateOldTime = CurTime;
			m_nGrade = 0;
			++m_nStage;
			Init();
			m_nGameState = DoREADY;
			//FMOD_Channel_Stop( g_Channel[6] );  // 미션 성공 사운드 출력 중지					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY 사운드 출력
		}
		break;
	}
}
void DudogiGame::Render()
{
	int i;
	char string[100];

	Screen::ScreenClear();

	switch (m_nGameState)
	{
	case DoINIT:
		if (m_nStage == 0)
			InitScreen();
		break;

	case DoREADY:
		ReadyScreen();
		sprintf(string, "%d", m_nStage + 1);
		Screen::Screen::ScreenPrint(16, 11, string);
		break;

	case DoRUNNING:
		RunningScreen();

		sprintf(string, "목표 두더지 : %d  잡은 두더지 : %d", m_StageInfo[m_nStage].nCatchDudagi, m_nDudagiCount);
		Screen::ScreenPrint(2, 1, string);
		sprintf(string, "스테이지 : %d 점수 : %d 남은 시간 : %d ", m_nStage + 1, m_nGrade, m_RemainTime);
		Screen::ScreenPrint(2, 2, string);

		for (i = 0; i < 9; i++)
		{
			if (m_Dudagi[i].nState == DoUP)
				Screen::ScreenPrint(m_Point[i].nX, m_Point[i].nY, "●");

			Screen::ScreenPrint(m_Point[i].nX, m_Point[i].nY + 1, "♨");
		}

		if (m_Mangchi.nIsAttack)
			Mangchi(m_Point[m_Mangchi.nIndex].nX, m_Point[m_Mangchi.nIndex].nY);
		else
			MangchiReady(m_Mangchi.nStayX, m_Mangchi.nStayY);
		break;

	case DoSUCCESS:
		SuccessScreen();
		sprintf(string, "%d", m_nStage + 1);
		Screen::ScreenPrint(20, 11, string);
		sprintf(string, "%d", m_nDudagiCount);
		Screen::ScreenPrint(21, 17, string);
		sprintf(string, "%d", m_nTotalGrade);
		Screen::ScreenPrint(14, 19, string);
		break;

	case DoFAILED:
		FailureScreen();
		sprintf(string, "%d", m_nStage + 1);
		Screen::ScreenPrint(16, 11, string);
		break;

	case DoRESULT:
		ResultScreen();
		sprintf(string, "%d", m_nTotalGrade);
		Screen::ScreenPrint(25, 11, string);
		break;
	}
	Screen::ScreenFlipping();
}
void DudogiGame::Release()
{}

void DudogiGame::Run()
{
	int nKey;

	Screen::ScreenInit();
	Init();        // 초기화

	while (1)
	{
		if (_kbhit())
		{
			if (m_nGameState == DoRESULT)
				break;

			nKey = _getch();
			switch (nKey)
			{
			case ' ':
				if (m_nGameState == DoINIT && m_nStage == 0)
				{
					m_nGameState = DoREADY;
					//FMOD_Channel_Stop( g_Channel[0] ); // 배경음 중지
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY 사운드 출력
					m_UpdateOldTime = clock();  // ready를 일정시간 지속해 주기 위해 							
				}
				break;
			case '1':  // 망치 키 입력 1 ~ 9까지
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (m_Mangchi.nIsAttack == 0 && m_nGameState == DoRUNNING)
				{
					m_Mangchi.nIndex = nKey - '1';
					m_Mangchi.StartTime = clock();
					m_Mangchi.nIsAttack = 1;
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5] );
				}
				break;

			case 'y':
			case 'Y':
				if (m_nGameState == DoFAILED)
				{
					Init();
					m_nGameState = DoREADY;
					//FMOD_Channel_Stop( g_Channel[1] );  // 미션 실패 사운드 출력 중지 
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY 사운드 출력
					m_nGrade = 0;
					m_UpdateOldTime = clock();
				}
				break;
			case 'n':
			case 'N':
				if (m_nGameState == DoFAILED)
				{
					m_nGameState = DoRESULT;
					//FMOD_Channel_Stop( g_Channel[1] );  // 미션 실패 사운드 출력 중지							
				}
				break;
			}
		}

		Update();    // 데이터 갱신
		Render();    // 화면 출력
					 //FMOD_System_Update( g_System );
	}
	Release();
	Screen::ScreenRelease();
}

void DudogiGame::Mangchi(int x, int y)
{
	Screen::ScreenPrint(x - 4, y - 1, "☆┏━┓");
	Screen::ScreenPrint(x - 4, y, "⊂┃꽝┃〓〓⊂⊃");
	Screen::ScreenPrint(x - 4, y + 1, "☆┗━┛");
}

void DudogiGame::MangchiReady(int x, int y)
{
	Screen::ScreenPrint(x - 4, y - 2, "    ∩");
	Screen::ScreenPrint(x - 4, y - 1, "  ┏━┓");
	Screen::ScreenPrint(x - 4, y, "  ┃  ┃");
	Screen::ScreenPrint(x - 4, y + 1, "  ┗━┛");
	Screen::ScreenPrint(x - 4, y + 2, "    ∥");
	Screen::ScreenPrint(x - 4, y + 3, "    ∥");
	Screen::ScreenPrint(x - 4, y + 4, "    ∩");
	Screen::ScreenPrint(x - 4, y + 5, "    ∪");
}

void DudogiGame::InitScreen()
{
	Screen::ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	Screen::ScreenPrint(0, 1, "┃                                        ┃");
	Screen::ScreenPrint(0, 2, "┃                                        ┃");
	Screen::ScreenPrint(0, 3, "┃                                        ┃");
	Screen::ScreenPrint(0, 4, "┃                                        ┃");
	Screen::ScreenPrint(0, 5, "┃                                        ┃");
	Screen::ScreenPrint(0, 6, "┃                                        ┃");
	Screen::ScreenPrint(0, 7, "┃                                        ┃");
	Screen::ScreenPrint(0, 8, "┃             ////////                   ┃");
	Screen::ScreenPrint(0, 9, "┃             ┃＼ /┃ ＼│/             ┃");
	Screen::ScreenPrint(0, 10, "┃             ┃··┃┏┳┳┓           ┃");
	Screen::ScreenPrint(0, 11, "┃             ┗┓┏┛┗┓┏┛           ┃");
	Screen::ScreenPrint(0, 12, "┃                                        ┃");
	Screen::ScreenPrint(0, 13, "┃                                        ┃");
	Screen::ScreenPrint(0, 14, "┃                                        ┃");
	Screen::ScreenPrint(0, 15, "┃             두더지 잡기 게임           ┃");
	Screen::ScreenPrint(0, 16, "┃                                        ┃");
	Screen::ScreenPrint(0, 17, "┃          space 키를 눌러주세요         ┃");
	Screen::ScreenPrint(0, 18, "┃                                        ┃");
	Screen::ScreenPrint(0, 19, "┃                                        ┃");
	Screen::ScreenPrint(0, 20, "┃                                        ┃");
	Screen::ScreenPrint(0, 21, "┃                                        ┃");
	Screen::ScreenPrint(0, 22, "┃                                        ┃");
	Screen::ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void DudogiGame::ReadyScreen()
{
	Screen::ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	Screen::ScreenPrint(0, 1, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 2, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 3, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 4, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 5, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 6, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 7, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 8, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 9, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 10, "┃■■■■■                    ■■■■■┃");
	Screen::ScreenPrint(0, 11, "┃■■■■■        스테이지    ■■■■■┃");
	Screen::ScreenPrint(0, 12, "┃■■■■■                    ■■■■■┃");
	Screen::ScreenPrint(0, 13, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 14, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 15, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 16, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 17, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 18, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 19, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 20, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 21, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 22, "┃■■■■■■■■■■■■■■■■■■■■┃");
	Screen::ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void DudogiGame::SuccessScreen()
{
	Screen::ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	Screen::ScreenPrint(0, 1, "┃                                        ┃");
	Screen::ScreenPrint(0, 2, "┃                                        ┃");
	Screen::ScreenPrint(0, 3, "┃                                        ┃");
	Screen::ScreenPrint(0, 4, "┃             // / // ＼＼＼             ┃");
	Screen::ScreenPrint(0, 5, "┃             │/＼    /＼│♬           ┃");
	Screen::ScreenPrint(0, 6, "┃             │≡  ▽  ≡│○           ┃");
	Screen::ScreenPrint(0, 7, "┃              ＼_________///            ┃");
	Screen::ScreenPrint(0, 8, "┃                                        ┃");
	Screen::ScreenPrint(0, 9, "┃                                        ┃");
	Screen::ScreenPrint(0, 10, "┃                                        ┃");
	Screen::ScreenPrint(0, 11, "┃                       스테이지         ┃");
	Screen::ScreenPrint(0, 12, "┃                                        ┃");
	Screen::ScreenPrint(0, 13, "┃                   미션 성공 !!!!       ┃");
	Screen::ScreenPrint(0, 14, "┃                                        ┃");
	Screen::ScreenPrint(0, 15, "┃                                        ┃");
	Screen::ScreenPrint(0, 16, "┃                                        ┃");
	Screen::ScreenPrint(0, 17, "┃     잡은 두더지 :                      ┃");
	Screen::ScreenPrint(0, 18, "┃                                        ┃");
	Screen::ScreenPrint(0, 19, "┃     총점 :                             ┃");
	Screen::ScreenPrint(0, 20, "┃                                        ┃");
	Screen::ScreenPrint(0, 21, "┃                                        ┃");
	Screen::ScreenPrint(0, 22, "┃                                        ┃");
	Screen::ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void DudogiGame::RunningScreen()
{
	Screen::ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	Screen::ScreenPrint(0, 1, "┃                                        ┃");
	Screen::ScreenPrint(0, 2, "┃                                        ┃");
	Screen::ScreenPrint(0, 3, "┃                                        ┃");
	Screen::ScreenPrint(0, 4, "┃                                        ┃");
	Screen::ScreenPrint(0, 5, "┃                                        ┃");
	Screen::ScreenPrint(0, 6, "┃                                        ┃");
	Screen::ScreenPrint(0, 7, "┃                                        ┃");
	Screen::ScreenPrint(0, 8, "┃                                        ┃");
	Screen::ScreenPrint(0, 9, "┃                                        ┃");
	Screen::ScreenPrint(0, 10, "┃                                        ┃");
	Screen::ScreenPrint(0, 11, "┃                                        ┃");
	Screen::ScreenPrint(0, 12, "┃                                        ┃");
	Screen::ScreenPrint(0, 13, "┃                                        ┃");
	Screen::ScreenPrint(0, 14, "┃                                        ┃");
	Screen::ScreenPrint(0, 15, "┃                                        ┃");
	Screen::ScreenPrint(0, 16, "┃                                        ┃");
	Screen::ScreenPrint(0, 17, "┃                                        ┃");
	Screen::ScreenPrint(0, 18, "┃                                        ┃");
	Screen::ScreenPrint(0, 19, "┃                            ○    ●    ┃");
	Screen::ScreenPrint(0, 20, "┃                          ┏■┛┏□┛  ┃");
	Screen::ScreenPrint(0, 21, "┃                            ┛┓  ┛┓  ┃");
	Screen::ScreenPrint(0, 22, "┃                                        ┃");
	Screen::ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void DudogiGame::FailureScreen()
{
	Screen::ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	Screen::ScreenPrint(0, 1, "┃                                        ┃");
	Screen::ScreenPrint(0, 2, "┃                                        ┃");
	Screen::ScreenPrint(0, 3, "┃                                        ┃");
	Screen::ScreenPrint(0, 4, "┃                                        ┃");
	Screen::ScreenPrint(0, 5, "┃                                        ┃");
	Screen::ScreenPrint(0, 6, "┃             ┎-━━-┒                 ┃");
	Screen::ScreenPrint(0, 7, "┃             d ご,.ご b                 ┃");
	Screen::ScreenPrint(0, 8, "┃             ┃┭─┮┃                 ┃");
	Screen::ScreenPrint(0, 9, "┃             ┖┦│┞┚                 ┃");
	Screen::ScreenPrint(0, 10, "┃               ┕┷┙                   ┃");
	Screen::ScreenPrint(0, 11, "┃                    스테이지            ┃");
	Screen::ScreenPrint(0, 12, "┃                                        ┃");
	Screen::ScreenPrint(0, 13, "┃            미션 실패 !!!!              ┃");
	Screen::ScreenPrint(0, 14, "┃                                        ┃");
	Screen::ScreenPrint(0, 15, "┃                                        ┃");
	Screen::ScreenPrint(0, 16, "┃                                        ┃");
	Screen::ScreenPrint(0, 17, "┃      다시 하시겠습니까? ( y/n )        ┃");
	Screen::ScreenPrint(0, 18, "┃                                        ┃");
	Screen::ScreenPrint(0, 19, "┃                                        ┃");
	Screen::ScreenPrint(0, 20, "┃                                        ┃");
	Screen::ScreenPrint(0, 21, "┃                                        ┃");
	Screen::ScreenPrint(0, 22, "┃                                        ┃");
	Screen::ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

// Note: 실패 했을 경우에 출력되면서 다시 할것인지를 묻는 화면이다.

void DudogiGame::ResultScreen()
{
	Screen::ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	Screen::ScreenPrint(0, 1, "┃                                        ┃");
	Screen::ScreenPrint(0, 2, "┃                                        ┃");
	Screen::ScreenPrint(0, 3, "┃                                        ┃");
	Screen::ScreenPrint(0, 4, "┃                                        ┃");
	Screen::ScreenPrint(0, 5, "┃                                        ┃");
	Screen::ScreenPrint(0, 6, "┃                                        ┃");
	Screen::ScreenPrint(0, 7, "┃  (((    두더지 잡기 게임 Score  ))))   ┃");
	Screen::ScreenPrint(0, 8, "┃                                        ┃");
	Screen::ScreenPrint(0, 9, "┃                                        ┃");
	Screen::ScreenPrint(0, 10, "┃                                        ┃");
	Screen::ScreenPrint(0, 11, "┃           총 점수  :                   ┃");
	Screen::ScreenPrint(0, 12, "┃                                        ┃");
	Screen::ScreenPrint(0, 13, "┃                                        ┃");
	Screen::ScreenPrint(0, 14, "┃                                        ┃");
	Screen::ScreenPrint(0, 15, "┃                                        ┃");
	Screen::ScreenPrint(0, 16, "┃                                        ┃");
	Screen::ScreenPrint(0, 17, "┃                                        ┃");
	Screen::ScreenPrint(0, 18, "┃                                        ┃");
	Screen::ScreenPrint(0, 19, "┃                                        ┃");
	Screen::ScreenPrint(0, 20, "┃                                        ┃");
	Screen::ScreenPrint(0, 21, "┃                                        ┃");
	Screen::ScreenPrint(0, 22, "┃                                        ┃");
	Screen::ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}