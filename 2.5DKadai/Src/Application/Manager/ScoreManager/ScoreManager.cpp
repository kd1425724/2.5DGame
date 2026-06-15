#include "ScoreManager.h"

void ScoreManager::Init()
{
	//スコアリセット
	m_score.score = 0;
}

void ScoreManager::Update()
{
	if (m_coinDownFlg)
	{
		m_coinnum -= m_coinDownSpd;

		if (m_coinnum <= m_targetCoin)
		{
			m_coinnum = m_targetCoin;
			m_coinDownFlg = false;
		}
	}
}

void ScoreManager::CoinDown(int time, int num)
{
	m_targetCoin = num;

	// 1フレームあたりに減らす量
	m_coinDownSpd = (float)(m_coinnum - num) / time;

	m_coinDownFlg = true;
}

