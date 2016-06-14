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

	if (m_nStage == -1) // 1���� �ʱ�ȭ�� �Ǵ� �κп� ���� ó�� ����
	{
		m_nStage = 0;
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0] );
	}

	m_nDudagiCount = 0; // ���� �δ��� ����	
	m_nGrade = 0;

	// Note: ��ġ �¾�
	m_Mangchi.nIsAttack = 0;
	m_Mangchi.nIndex = 0;
	m_Mangchi.nStayX = 38;
	m_Mangchi.nStayY = 10;
	m_Mangchi.StartTime = m_GameStartTime;
	m_Mangchi.DelayTime = 300;

	for (i = 0; i < 9; i++)
	{
		m_Dudagi[i].StayTime = rand() % m_StageInfo[m_nStage].DownLimitTime + 10; // Note: �ּ� 10�� �ȴ�.
		m_Dudagi[i].OldTime = clock();
		m_Dudagi[i].nState = DoSETUP;
		m_Dudagi[i].OutPutTime = rand() % m_StageInfo[m_nStage].UpLimitTime + 10; //�ּ� 10�� �ȴ�.
	}
}
void DudogiGame::Update()
{
	int i;
	clock_t CurTime = clock();

	switch (m_nGameState)
	{
	case DoREADY:
		if (CurTime - m_UpdateOldTime > 2000)  // 2��
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
			// �δ��� ������Ʈ	
			for (i = 0; i < 9; i++)
			{
				switch (m_Dudagi[i].nState)
				{
				case DoSETUP:
					m_Dudagi[i].OldTime = CurTime;
					m_Dudagi[i].OutPutTime = rand() % (int)m_StageInfo[m_nStage].UpLimitTime + 10;
					m_Dudagi[i].StayTime = rand() % (int)m_StageInfo[m_nStage].DownLimitTime + 10;
					m_Dudagi[i].nState = DoUP;
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3] ); // ���ö��� ���
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

			// ��ġ ������Ʈ 
			if (m_Mangchi.nIsAttack)
			{
				// �浹 �׽�Ʈ ��ġ�� ���� �ϳ��� �δ����� ���� �� �ֱ⿡ �ϳ��� ������� �浹 üũ�� ���� ���´�.
				for (i = 0; i < 9; i++)
				{
					if (m_Dudagi[i].nState == DoUP && i == m_Mangchi.nIndex)
					{
						m_nGrade += 10;
						m_nDudagiCount++;
						m_Dudagi[i].nState = DoDOWN; // �׾����� �ٿ� ���·� �ٷ� ��ȯ�� �ϵ��� �Ѵ�.															
												   //FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4] );								
						break;
					}
				}

				// Note: ��ġ�� ���¸� �������ִ� �κ� ��ġ�� ���� ���� ������ �ð� ���� �ӹ����� �ϱ� ���� �κ�
				if (CurTime - m_Mangchi.StartTime > m_Mangchi.DelayTime)
				{
					m_Mangchi.nIsAttack = 0;
				}
			}

			m_RemainTime = (m_StageInfo[m_nStage].LimitTime - (CurTime - m_GameStartTime)) / 3000; // ���� ���� ���� �ð�
		}
		break;
	case DoSTOP:
		// �����̳� ���и� �Ǵ����־ ����� ���ִ� �κ��� �;� �Ѵ�.
		if (m_nDudagiCount >= m_StageInfo[m_nStage].nCatchDudagi)
		{
			m_UpdateOldTime = CurTime;
			m_nGameState = DoSUCCESS;
			m_nTotalGrade += m_nGrade;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6] ); // �̼� ���� ����
		}
		else {
			m_nGameState = DoFAILED;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1] ); // �̼� ���� ����
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
			//FMOD_Channel_Stop( g_Channel[6] );  // �̼� ���� ���� ��� ����					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY ���� ���
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

		sprintf(string, "��ǥ �δ��� : %d  ���� �δ��� : %d", m_StageInfo[m_nStage].nCatchDudagi, m_nDudagiCount);
		Screen::ScreenPrint(2, 1, string);
		sprintf(string, "�������� : %d ���� : %d ���� �ð� : %d ", m_nStage + 1, m_nGrade, m_RemainTime);
		Screen::ScreenPrint(2, 2, string);

		for (i = 0; i < 9; i++)
		{
			if (m_Dudagi[i].nState == DoUP)
				Screen::ScreenPrint(m_Point[i].nX, m_Point[i].nY, "��");

			Screen::ScreenPrint(m_Point[i].nX, m_Point[i].nY + 1, "��");
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
	Init();        // �ʱ�ȭ

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
					//FMOD_Channel_Stop( g_Channel[0] ); // ����� ����
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY ���� ���
					m_UpdateOldTime = clock();  // ready�� �����ð� ������ �ֱ� ���� 							
				}
				break;
			case '1':  // ��ġ Ű �Է� 1 ~ 9����
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
					//FMOD_Channel_Stop( g_Channel[1] );  // �̼� ���� ���� ��� ���� 
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY ���� ���
					m_nGrade = 0;
					m_UpdateOldTime = clock();
				}
				break;
			case 'n':
			case 'N':
				if (m_nGameState == DoFAILED)
				{
					m_nGameState = DoRESULT;
					//FMOD_Channel_Stop( g_Channel[1] );  // �̼� ���� ���� ��� ����							
				}
				break;
			}
		}

		Update();    // ������ ����
		Render();    // ȭ�� ���
					 //FMOD_System_Update( g_System );
	}
	Release();
	Screen::ScreenRelease();
}

void DudogiGame::Mangchi(int x, int y)
{
	Screen::ScreenPrint(x - 4, y - 1, "�٦�����");
	Screen::ScreenPrint(x - 4, y, "�����Φ�������");
	Screen::ScreenPrint(x - 4, y + 1, "�٦�����");
}

void DudogiGame::MangchiReady(int x, int y)
{
	Screen::ScreenPrint(x - 4, y - 2, "    ��");
	Screen::ScreenPrint(x - 4, y - 1, "  ������");
	Screen::ScreenPrint(x - 4, y, "  ��  ��");
	Screen::ScreenPrint(x - 4, y + 1, "  ������");
	Screen::ScreenPrint(x - 4, y + 2, "    ��");
	Screen::ScreenPrint(x - 4, y + 3, "    ��");
	Screen::ScreenPrint(x - 4, y + 4, "    ��");
	Screen::ScreenPrint(x - 4, y + 5, "    ��");
}

void DudogiGame::InitScreen()
{
	Screen::ScreenPrint(0, 0, "��������������������������������������������");
	Screen::ScreenPrint(0, 1, "��                                        ��");
	Screen::ScreenPrint(0, 2, "��                                        ��");
	Screen::ScreenPrint(0, 3, "��                                        ��");
	Screen::ScreenPrint(0, 4, "��                                        ��");
	Screen::ScreenPrint(0, 5, "��                                        ��");
	Screen::ScreenPrint(0, 6, "��                                        ��");
	Screen::ScreenPrint(0, 7, "��                                        ��");
	Screen::ScreenPrint(0, 8, "��             ////////                   ��");
	Screen::ScreenPrint(0, 9, "��             ���� /�� ����/             ��");
	Screen::ScreenPrint(0, 10, "��             ����������������           ��");
	Screen::ScreenPrint(0, 11, "��             ����������������           ��");
	Screen::ScreenPrint(0, 12, "��                                        ��");
	Screen::ScreenPrint(0, 13, "��                                        ��");
	Screen::ScreenPrint(0, 14, "��                                        ��");
	Screen::ScreenPrint(0, 15, "��             �δ��� ��� ����           ��");
	Screen::ScreenPrint(0, 16, "��                                        ��");
	Screen::ScreenPrint(0, 17, "��          space Ű�� �����ּ���         ��");
	Screen::ScreenPrint(0, 18, "��                                        ��");
	Screen::ScreenPrint(0, 19, "��                                        ��");
	Screen::ScreenPrint(0, 20, "��                                        ��");
	Screen::ScreenPrint(0, 21, "��                                        ��");
	Screen::ScreenPrint(0, 22, "��                                        ��");
	Screen::ScreenPrint(0, 23, "��������������������������������������������");
}

void DudogiGame::ReadyScreen()
{
	Screen::ScreenPrint(0, 0, "��������������������������������������������");
	Screen::ScreenPrint(0, 1, "����������������������᦭");
	Screen::ScreenPrint(0, 2, "����������������������᦭");
	Screen::ScreenPrint(0, 3, "����������������������᦭");
	Screen::ScreenPrint(0, 4, "����������������������᦭");
	Screen::ScreenPrint(0, 5, "����������������������᦭");
	Screen::ScreenPrint(0, 6, "����������������������᦭");
	Screen::ScreenPrint(0, 7, "����������������������᦭");
	Screen::ScreenPrint(0, 8, "����������������������᦭");
	Screen::ScreenPrint(0, 9, "����������������������᦭");
	Screen::ScreenPrint(0, 10, "��������                    �����᦭");
	Screen::ScreenPrint(0, 11, "��������        ��������    �����᦭");
	Screen::ScreenPrint(0, 12, "��������                    �����᦭");
	Screen::ScreenPrint(0, 13, "����������������������᦭");
	Screen::ScreenPrint(0, 14, "����������������������᦭");
	Screen::ScreenPrint(0, 15, "����������������������᦭");
	Screen::ScreenPrint(0, 16, "����������������������᦭");
	Screen::ScreenPrint(0, 17, "����������������������᦭");
	Screen::ScreenPrint(0, 18, "����������������������᦭");
	Screen::ScreenPrint(0, 19, "����������������������᦭");
	Screen::ScreenPrint(0, 20, "����������������������᦭");
	Screen::ScreenPrint(0, 21, "����������������������᦭");
	Screen::ScreenPrint(0, 22, "����������������������᦭");
	Screen::ScreenPrint(0, 23, "��������������������������������������������");
}

void DudogiGame::SuccessScreen()
{
	Screen::ScreenPrint(0, 0, "��������������������������������������������");
	Screen::ScreenPrint(0, 1, "��                                        ��");
	Screen::ScreenPrint(0, 2, "��                                        ��");
	Screen::ScreenPrint(0, 3, "��                                        ��");
	Screen::ScreenPrint(0, 4, "��             // / // ������             ��");
	Screen::ScreenPrint(0, 5, "��             ��/��    /������           ��");
	Screen::ScreenPrint(0, 6, "��             ����  ��  �զ���           ��");
	Screen::ScreenPrint(0, 7, "��              ��_________///            ��");
	Screen::ScreenPrint(0, 8, "��                                        ��");
	Screen::ScreenPrint(0, 9, "��                                        ��");
	Screen::ScreenPrint(0, 10, "��                                        ��");
	Screen::ScreenPrint(0, 11, "��                       ��������         ��");
	Screen::ScreenPrint(0, 12, "��                                        ��");
	Screen::ScreenPrint(0, 13, "��                   �̼� ���� !!!!       ��");
	Screen::ScreenPrint(0, 14, "��                                        ��");
	Screen::ScreenPrint(0, 15, "��                                        ��");
	Screen::ScreenPrint(0, 16, "��                                        ��");
	Screen::ScreenPrint(0, 17, "��     ���� �δ��� :                      ��");
	Screen::ScreenPrint(0, 18, "��                                        ��");
	Screen::ScreenPrint(0, 19, "��     ���� :                             ��");
	Screen::ScreenPrint(0, 20, "��                                        ��");
	Screen::ScreenPrint(0, 21, "��                                        ��");
	Screen::ScreenPrint(0, 22, "��                                        ��");
	Screen::ScreenPrint(0, 23, "��������������������������������������������");
}

void DudogiGame::RunningScreen()
{
	Screen::ScreenPrint(0, 0, "��������������������������������������������");
	Screen::ScreenPrint(0, 1, "��                                        ��");
	Screen::ScreenPrint(0, 2, "��                                        ��");
	Screen::ScreenPrint(0, 3, "��                                        ��");
	Screen::ScreenPrint(0, 4, "��                                        ��");
	Screen::ScreenPrint(0, 5, "��                                        ��");
	Screen::ScreenPrint(0, 6, "��                                        ��");
	Screen::ScreenPrint(0, 7, "��                                        ��");
	Screen::ScreenPrint(0, 8, "��                                        ��");
	Screen::ScreenPrint(0, 9, "��                                        ��");
	Screen::ScreenPrint(0, 10, "��                                        ��");
	Screen::ScreenPrint(0, 11, "��                                        ��");
	Screen::ScreenPrint(0, 12, "��                                        ��");
	Screen::ScreenPrint(0, 13, "��                                        ��");
	Screen::ScreenPrint(0, 14, "��                                        ��");
	Screen::ScreenPrint(0, 15, "��                                        ��");
	Screen::ScreenPrint(0, 16, "��                                        ��");
	Screen::ScreenPrint(0, 17, "��                                        ��");
	Screen::ScreenPrint(0, 18, "��                                        ��");
	Screen::ScreenPrint(0, 19, "��                            ��    ��    ��");
	Screen::ScreenPrint(0, 20, "��                          ���ᦰ���র  ��");
	Screen::ScreenPrint(0, 21, "��                            ����  ����  ��");
	Screen::ScreenPrint(0, 22, "��                                        ��");
	Screen::ScreenPrint(0, 23, "��������������������������������������������");
}

void DudogiGame::FailureScreen()
{
	Screen::ScreenPrint(0, 0, "��������������������������������������������");
	Screen::ScreenPrint(0, 1, "��                                        ��");
	Screen::ScreenPrint(0, 2, "��                                        ��");
	Screen::ScreenPrint(0, 3, "��                                        ��");
	Screen::ScreenPrint(0, 4, "��                                        ��");
	Screen::ScreenPrint(0, 5, "��                                        ��");
	Screen::ScreenPrint(0, 6, "��             ��-����-��                 ��");
	Screen::ScreenPrint(0, 7, "��             d ��,.�� b                 ��");
	Screen::ScreenPrint(0, 8, "��             ���Ѧ��Ҧ�                 ��");
	Screen::ScreenPrint(0, 9, "��             �Ŧͦ��ɦ�                 ��");
	Screen::ScreenPrint(0, 10, "��               �Ʀ���                   ��");
	Screen::ScreenPrint(0, 11, "��                    ��������            ��");
	Screen::ScreenPrint(0, 12, "��                                        ��");
	Screen::ScreenPrint(0, 13, "��            �̼� ���� !!!!              ��");
	Screen::ScreenPrint(0, 14, "��                                        ��");
	Screen::ScreenPrint(0, 15, "��                                        ��");
	Screen::ScreenPrint(0, 16, "��                                        ��");
	Screen::ScreenPrint(0, 17, "��      �ٽ� �Ͻðڽ��ϱ�? ( y/n )        ��");
	Screen::ScreenPrint(0, 18, "��                                        ��");
	Screen::ScreenPrint(0, 19, "��                                        ��");
	Screen::ScreenPrint(0, 20, "��                                        ��");
	Screen::ScreenPrint(0, 21, "��                                        ��");
	Screen::ScreenPrint(0, 22, "��                                        ��");
	Screen::ScreenPrint(0, 23, "��������������������������������������������");
}

// Note: ���� ���� ��쿡 ��µǸ鼭 �ٽ� �Ұ������� ���� ȭ���̴�.

void DudogiGame::ResultScreen()
{
	Screen::ScreenPrint(0, 0, "��������������������������������������������");
	Screen::ScreenPrint(0, 1, "��                                        ��");
	Screen::ScreenPrint(0, 2, "��                                        ��");
	Screen::ScreenPrint(0, 3, "��                                        ��");
	Screen::ScreenPrint(0, 4, "��                                        ��");
	Screen::ScreenPrint(0, 5, "��                                        ��");
	Screen::ScreenPrint(0, 6, "��                                        ��");
	Screen::ScreenPrint(0, 7, "��  (((    �δ��� ��� ���� Score  ))))   ��");
	Screen::ScreenPrint(0, 8, "��                                        ��");
	Screen::ScreenPrint(0, 9, "��                                        ��");
	Screen::ScreenPrint(0, 10, "��                                        ��");
	Screen::ScreenPrint(0, 11, "��           �� ����  :                   ��");
	Screen::ScreenPrint(0, 12, "��                                        ��");
	Screen::ScreenPrint(0, 13, "��                                        ��");
	Screen::ScreenPrint(0, 14, "��                                        ��");
	Screen::ScreenPrint(0, 15, "��                                        ��");
	Screen::ScreenPrint(0, 16, "��                                        ��");
	Screen::ScreenPrint(0, 17, "��                                        ��");
	Screen::ScreenPrint(0, 18, "��                                        ��");
	Screen::ScreenPrint(0, 19, "��                                        ��");
	Screen::ScreenPrint(0, 20, "��                                        ��");
	Screen::ScreenPrint(0, 21, "��                                        ��");
	Screen::ScreenPrint(0, 22, "��                                        ��");
	Screen::ScreenPrint(0, 23, "��������������������������������������������");
}