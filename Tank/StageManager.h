#pragma once

class StageManager
{
private:
	explicit StageManager();
	~StageManager();
	StageManager(const StageManager&);
	StageManager& operator=(const StageManager&);

private:
	int stageLevel;
	int playerCount;
	int enemyCount;
	int killCount;
	int score;
	static StageManager* instance;

public:
	static StageManager* GetInstance();
	static void Release();

	inline void SetNextStage()
	{
		++stageLevel;
		ReSetStage();
	}

	inline void ReSetStage()
	{
		playerCount = 3;
		enemyCount = 9;
		killCount = 0;
		score = 0;
	}

    inline bool CheckMissionClear()
	{
		if (enemyCount <= killCount)
			return true;

		return false;
	}

	inline bool CheckGameEnd()
	{
		if (playerCount > 0)
			return false;
		return true;
	}

	inline void AddKillCount()
	{
		++killCount;
	}

	inline void AddScore()
	{
		score += 10;
	}

	inline void LostLife()
	{
		--playerCount;
	}

	void ShowUi();
	void ShowResult();
	void ShowIntro();
	void ShowSucess();
	void ShowFail();
};