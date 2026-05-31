#pragma once
#include"../EnemyBase.h"

class Slime:public EnemyBase
{
public:
	Slime() { Init(); }
	~Slime()override { Release(); }

	void Update()override;
	void DrawLit()override;

private:

	void Init()override;

	void Release();

	//固有行動パターン用
	enum class SlimePattern
	{
		Stop,	//待機
		Jump	//ジャンプ
	};

	SlimePattern m_slimepattern = SlimePattern::Stop;

	void StopInit();
	void StopUpdate();

	static const int StopTime = 30;
	int m_stoptime = StopTime;

	void JumpInit();
	void JumpUpdate();

	

	
};
