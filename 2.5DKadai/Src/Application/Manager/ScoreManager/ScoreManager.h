#pragma once

struct Score
{
	int score = 0;
};
class ScoreManager
{
public:
	
	void Init();
	void Update();

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
	UINT GetCoin() { return (UINT)m_coinnum; }

	//コイン減少
	void CoinDown(int time, int num);

private:
	//スコア用変数
	Score m_score;

	//コイン取得
	float m_coinnum = 0;

	float m_coinDownSpd = 0.0f;
	int m_targetCoin = 0;
	bool m_coinDownFlg = false;

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
