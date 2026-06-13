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

	//コイン取得
	void CoinUp() { m_coinnum++; }
	//コイン取得数取得
	UINT GetCoin() { return m_coinnum; }

private:
	//スコア用変数
	Score m_score;

	//コイン取得
	UINT m_coinnum = 0;

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
