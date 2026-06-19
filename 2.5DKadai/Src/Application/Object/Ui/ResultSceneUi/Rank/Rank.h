#pragma once
#include"../../UiBase.h"
class Rank :public UiBase
{
public:

	enum RankPattern
	{
		Stop,
		Shuffle,
		End
	};

	enum RankNum
	{
		BRank,
		ARank,
		SRank,
		RankNum
	};

	Rank() {}
	~Rank() override {}

	void Init() override;
	void Update() override;
	void DrawSprite() override;

private:

	std::shared_ptr<KdTexture> m_Branktex;
	std::shared_ptr<KdTexture> m_Aranktex;
	std::shared_ptr<KdTexture> m_Sranktex;

	RankPattern m_pattern = Stop;

	//現在の表示ランク
	int m_nowRank = BRank;

	//最終ランク
	int m_endanim = BRank;

	//シャッフル時間
	int m_shuffleCnt = 0;

	//ランク切り替え間隔
	int m_changeInterval = 2;

	//開始まで待つ時間
	int m_stoptime = 30;

	//拡大演出用
	float m_scaleAnim = 1.0f;

	float m_animcnt = 0;

	float m_anim[(int)RankNum] = { 0,107.6f,215.2f };

	//デフォルトのサイズ
	Math::Vector3 m_defaultscale = {};
};