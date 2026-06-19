#include "Rank.h"
#include"../../../../Manager/ScoreManager/ScoreManager.h"
#include"../../../Effect/EffectManager.h"
#include"../../../Effect/BaseEffect.h"
void Rank::Init()
{
	SetName("Rank");

	m_Sranktex = std::make_shared<KdTexture>();
	m_Sranktex->Load("Asset/Textures/ResultScene/Rank/RankS.png");

	m_Aranktex = std::make_shared<KdTexture>();
	m_Aranktex->Load("Asset/Textures/ResultScene/Rank/RankA.png");

	m_Branktex = std::make_shared<KdTexture>();
	m_Branktex->Load("Asset/Textures/ResultScene/Rank/RankB.png");

	UINT coin = SCOREMANAGER.GetCoin();

	if (coin >= 100)
	{
		m_endanim = SRank;
	}
	else if (coin >= 60)
	{
		m_endanim = ARank;
	}
	else
	{
		m_endanim = BRank;
	}

	m_pattern = Stop;

	m_nowRank = BRank;

	m_scaleAnim = 1.0f;

	m_defaultscale = { 2.0f,2.0f,1.0f };
	m_scale = m_defaultscale;

	m_scale.x /= 3;

	MatrixUpdate();
}

void Rank::Update()
{
	switch (m_pattern)
	{
	case Stop:

		m_stoptime--;

		if (m_stoptime <= 0)
		{
			m_pattern = Shuffle;

			m_shuffleCnt = 0;
			m_changeInterval = 2;
			m_nowRank = BRank;
		}

		break;

	case Shuffle:

		m_shuffleCnt++;

		//ランク切り替え
		if (m_shuffleCnt % m_changeInterval == 0)
		{
			m_nowRank++;

			if (m_nowRank >= RankNum)
			{
				m_nowRank = BRank;
			}
		}

		//徐々に減速
		if (m_shuffleCnt % 15 == 0)
		{
			m_changeInterval++;
		}

		//最終ランク決定
		if (m_shuffleCnt > 80)
		{
			m_nowRank = m_endanim;

			//バン！
			m_scaleAnim = 1.6f;

			EFFECT.CreateEffect(
				"CoinGet",
				m_pos,
				eBright);

			m_pattern = End;
		}

		break;

	case End:

		//大きさを元に戻す
		m_scaleAnim += (1.0f - m_scaleAnim) * 0.15f;

		break;

	default:
		break;
	}

	m_scale =
	{
		m_defaultscale.x * m_scaleAnim / 3 ,
		m_defaultscale.y* m_scaleAnim,
		m_defaultscale.z
	};

	if (m_shuffleCnt % m_changeInterval == 0)
	{
		m_animcnt++;

		if (m_animcnt >= RankNum)
		{
			m_animcnt = BRank;
		}

		m_nowRank = (int)m_animcnt;
	}

	MatrixUpdate();
}

void Rank::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);

	Math::Rectangle rect =
	{
		(long)m_anim[(int)m_nowRank],
		0,
		(long)107.6f,
		106
	};

	switch (m_nowRank)
	{
	case BRank:

		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_Branktex,
			0,
			0,
			&rect);

		break;

	case ARank:

		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_Aranktex,
			0,
			0,
			&rect);

		break;

	case SRank:

		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_Sranktex,
			0,
			0,
			&rect);

		break;

	default:
		break;
	}

	KdShaderManager::Instance().m_spriteShader.SetMatrix(
		Math::Matrix::Identity);
}