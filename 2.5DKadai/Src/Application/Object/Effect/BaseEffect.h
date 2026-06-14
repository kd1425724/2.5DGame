#pragma once

class BaseEffect : public KdGameObject
{
public:

	BaseEffect() {}
	~BaseEffect() override {}

	void Init() override;
	void Update() override;
	void DrawBright() override;
	void DrawLit()override;

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

	void SetLoop(bool loop)
	{
		m_loop = loop;
	}

private:

	std::shared_ptr<KdSquarePolygon> m_polygon;

	std::string m_assetName;

	UINT m_splitX = 1;
	UINT m_splitY = 1;

	std::vector<int> m_anim;

	float m_animCnt = 0;

	float m_animSpeed = 0.2f;

	bool m_loop = false;


};