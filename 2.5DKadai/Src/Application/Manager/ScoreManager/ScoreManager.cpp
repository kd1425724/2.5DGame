#include "ScoreManager.h"

void ScoreManager::Init()
{
	//スコアリセット
	m_score.score = 0;
	m_score.coin = 0;
}

void ScoreManager::Update()
{
	int i = 0;
	if (!m_coinDownFlg) return;

	m_coinDownCnt++;

	float rate = (float)m_coinDownCnt / m_coinDownTime;
	m_score.coin = m_startCoin - (UINT)((m_startCoin - m_targetCoin) * rate);

	if (m_coinDownCnt >= m_coinDownTime || m_score.coin <= m_targetCoin)
	{
		m_score.coin = m_targetCoin;
		m_coinDownFlg = false;
	}
}

void ScoreManager::CoinDown(int time, int num)
{
	m_startCoin = m_score.coin;

	m_targetCoin = num;

	m_coinDownTime = time;
	m_coinDownCnt = 0;

	m_coinDownRemain = 0.0f;

	m_coinDownFlg = true;
}

