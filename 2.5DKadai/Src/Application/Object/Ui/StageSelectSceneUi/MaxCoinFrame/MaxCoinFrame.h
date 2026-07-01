#pragma once

class Num;

class MaxCoinFrame : public KdGameObject
{
public:
	void Init() override;
	void Update() override;
	void DrawSprite() override;

private:

	//数字の数
	static const int NumNum = 3;

	std::shared_ptr<Num> m_num[NumNum];

	std::shared_ptr<KdTexture> m_tex;
};