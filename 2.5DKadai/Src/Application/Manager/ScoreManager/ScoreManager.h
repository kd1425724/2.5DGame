#pragma once

struct Score
{
	int score = 0;
};
class ScoreManager
{
public:
	
	void Init();

	//スコアセット
	void ScoreUp(const int& _val)
	{
		m_score.score += _val;
	}
	//スコア取得
	Score GetScore() { return m_score; }

private:
	//スコア用変数
	Score m_score;

private:
	ScoreManager() {}
	~ScoreManager() {}

public:

	static ScoreManager& Instance()
	{
		static ScoreManager instance;
		return instance;
	}
};

#define SCOREMANAGER ScoreManager::Instance()
