#pragma once
class Num;

class CountDown : public KdGameObject
{
public:

	enum CountPattern
	{
		Three,
		Two,
		One,
		Go,
		End
	};

	CountDown() {}
	~CountDown() override {}

	void Init() override;
	void Update() override;
	void DrawSprite() override;

	bool IsFinish() const
	{
		return m_pattern == Go;
	}

private:

	std::shared_ptr<KdTexture> m_goTex;

	std::shared_ptr<Num> m_num;

	CountPattern m_pattern = Three;

	int m_count = 0;

	int m_changeTime = 40;
};