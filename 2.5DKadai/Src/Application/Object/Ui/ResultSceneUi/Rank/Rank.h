#pragma once
#include"../../UiBase.h"
class Rank:public UiBase
{
public:
	Rank(){}
	~Rank()override {};

	void Init()override;
	void Update()override;
	void DrawSprite()override;

private:

	enum class RankPattern
	{
		Stop,
		Start,
		End
	};

	RankPattern m_pattern = RankPattern::Stop;

	static const int CoinCollectionTime = 120;

	static const int StopTime = 60;
	int m_stoptime = StopTime;

	UINT m_startcoin = 0;

	float m_animcnt = 0;

	int m_endanim = 0;

	std::vector<int> m_anim;
};
