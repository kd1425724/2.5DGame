#pragma once

class GoalDisplay : public KdGameObject
{
public:

	GoalDisplay() {}
	~GoalDisplay() override {}

	void Init() override;
	void Update() override;
	void DrawSprite() override;

	// 表示が終わったか
	bool IsFinish() const { return m_isFinish; }

private:

	std::shared_ptr<KdTexture> m_goalTex;

	// 表示タイマー
	int m_count = 0;

	// 表示時間(フレーム)
	static constexpr int DISPLAY_TIME = 120;

	// 表示中フラグ
	bool m_isVisible = false;

	// 表示終了フラグ
	bool m_isFinish = false;
};
