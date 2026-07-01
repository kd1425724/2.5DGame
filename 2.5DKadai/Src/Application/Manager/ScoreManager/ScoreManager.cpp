#include "ScoreManager.h"
#include"../../Common/Info/Info.h"
void ScoreManager::Init()
{
	//スコアリセット
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

void ScoreManager::Save()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "Asset/Data/ScoreData/ScoreData.csv", "w");

	if (!fp)return;

	for (int i = 0; i < (int)Stage::StageNum; i++)
	{
		fprintf(fp, "%u", m_score.maxcoin[i]);

		if (i != (int)Stage::StageNum - 1)
		{
			fprintf(fp, ",");
		}
	}

	fprintf(fp, "\n");

	fclose(fp);
}

void ScoreManager::Load()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "Asset/Data/ScoreData/ScoreData.csv", "r");

	if (!fp) return;

	for (int i = 0; i < (int)Stage::StageNum; i++)
	{
		fscanf_s(fp, "%u", &m_score.maxcoin[i]);

		// 最後以外はカンマを読み飛ばす
		if (i != (int)Stage::StageNum - 1)
		{
			fscanf_s(fp, ",");
		}
	}

	fclose(fp);
}
