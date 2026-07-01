#pragma once

struct Score
{
	UINT coin = 0;
	UINT maxcoin[3] = {};
};

enum class Stage
{
	None = -1,
	Stage1,
	Stage2,
	Stage3,
	StageNum
};
class ScoreManager
{
public:
	
	void Init();
	void Update();

	//コイン取得
	void CoinUp() { m_score.coin++; }
	//コイン取得数取得
	UINT GetCoin() { return m_score.coin; }

	//コイン減少開始
	void CoinDown(int time, int num);

	//スコア初期化
	void ScoreReset()
	{
		m_score.coin = 0;
	}

	//セーブ・ロード
	void Save();
	void Load();

	void SetMaxCoin(const Stage& stage)
	{
		if (stage == Stage::None)return;

		//スコアが現在の最大コイン数より低かったら
		if (m_score.maxcoin[(int)stage] > m_score.coin)return;

		m_score.maxcoin[(int)stage] = m_score.coin;
	}

	UINT GetMaxCoin(const Stage& stage)
	{
		if (stage == Stage::None)return 0;

		return m_score.maxcoin[(int)stage];
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
	ScoreManager() { Load(); }
	~ScoreManager() {}

public:

	static ScoreManager& Instance()
	{
		static ScoreManager instance;
		return instance;
	}
};

#define SCOREMANAGER ScoreManager::Instance()
