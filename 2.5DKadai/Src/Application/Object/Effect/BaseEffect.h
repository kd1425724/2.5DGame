#pragma once

enum EffectFlag
{
	eNone = 0,
	eBright = 1 << 0,
	eHoming = 1 << 1,
	eLoop = 1 << 2,
	eScroll = 1 << 3
};

class BaseEffect : public KdGameObject
{
public:

	BaseEffect() {}
	~BaseEffect() override {}

	void Init() override;
	void Update() override;
	void DrawBright() override;
	void DrawEffect()override;

	void SetAsset(const std::string& asset)
	{
		m_assetName = asset;
	}

	void SetSplit(UINT x, UINT y)
	{
		m_splitX = x;
		m_splitY = y;
	}

	void SetAnim(const std::vector<int>& anim)
	{
		m_anim = anim;
	}

	void SetAnimSpeed(float speed)
	{
		m_animSpeed = speed;
	}

	void SetFlag(UINT flag)
	{
		m_flag = flag;
	}

	bool CheckFlag(EffectFlag flag) const
	{
		return (m_flag & flag);
	}

	void SetTarget(const std::shared_ptr<KdGameObject>& target)
	{
		m_target = target;
	}

	void SetTargetPos(const Math::Vector3& pos)
	{
		m_targetPos = pos;
	}

	void SetHomingSpeed(float speed)
	{
		m_homingSpeed = speed;
	}

private:

	std::shared_ptr<KdSquarePolygon> m_polygon;

	std::string m_assetName;

	UINT m_splitX = 1;
	UINT m_splitY = 1;

	std::vector<int> m_anim;

	float m_animCnt = 0;

	float m_animSpeed = 0.2f;

	UINT m_flag = eNone;

	Math::Vector3 m_targetPos;
	std::weak_ptr<KdGameObject> m_target;

	float m_homingSpeed = 10.0f;
};