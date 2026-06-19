#pragma once

struct Score
{
	int score = 0;
	UINT coin = 0;
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
	void CoinUp() { m_score.coin++; }
	//コイン取得数取得
	UINT GetCoin() { return m_score.coin; }

	//コイン減少開始
	void CoinDown(int time, int num);

	//スコア初期化
	void ScoreReset()
	{
		m_score.score = 0;
		m_score.coin = 0;
	}

private:
	//スコア用変数
	Score m_score;


	//コイン減少用
	int m_targetCoin = 0;
	int m_coinDownTime = 0;
	int m_coinDownCnt = 0;
	float m_coinDownRemain = 0.0f;
	bool m_coinDownFlg = false;
	UINT m_startCoin = 0;

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
