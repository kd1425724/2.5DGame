#include "Rank.h"
#include"../../../../Manager/ScoreManager/ScoreManager.h"

void Rank::Init()
{
	SetName("Rank");

	m_tex = std::shared_ptr<KdTexture>();
	m_tex->Load("");

	m_startcoin = SCOREMANAGER.GetCoin();

	////始めにコイン枚数からどのランク（アニメーション）まで行くのか計算
	//if ()
	//{
	//	m_endanim =
	//}
	//else if ()
	//{
	//	m_endanim =
	//}

	//ファイル読み込み
	FILE* fp = nullptr;
}

void Rank::Update()
{
	switch (m_pattern)
	{
	case Rank::RankPattern::Stop:
		m_stoptime--;
		if (m_stoptime < 0)
		{
			//回収開始
			m_pattern = RankPattern::Start;
			//何フレームかけてどこまで下げるか
			SCOREMANAGER.CoinDown(CoinCollectionTime, 0);
		}
		break;
	case Rank::RankPattern::Start:
		//スコアのコインを少しずつ回収する演出をいれてコインが一定枚数行くごとにランクアップアニメーション
		if (SCOREMANAGER.GetCoin() > 0)
		{
			//コイン回収時間かけて最後のアニメーションまで
			/*float animcntup = (float)m_endanim / CoinCollectionTime;
			m_animcnt += animcntup;*/

			float rate = 1.0f - (float)SCOREMANAGER.GetCoin() / m_startcoin;
			m_animcnt = rate * m_endanim;
		}
		else
		{
			m_animcnt = m_endanim;
			m_pattern = RankPattern::End;
		}
		break;
	case Rank::RankPattern::End:
		break;
	default:
		break;
	}
}

void Rank::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);

	Math::Rectangle rect = { m_anim[(int)m_animcnt],0,30,30 };

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0,&rect);
	//行列初期化
	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}
