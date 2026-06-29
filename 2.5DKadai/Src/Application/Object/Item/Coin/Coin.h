#pragma once
#include"../BaseItem.h"

class Coin:public BaseItem
{
public:
	Coin(){}
	~Coin(){}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void DrawBright()override;

	void OnHit(KdGameObject* other)override;

	static void SetTarget(const std::shared_ptr<KdGameObject>& target) { s_target = target; }
private:

	bool m_getflg = false;

	float m_getTime = 0.0f;

	Math::Vector3 m_moveDir = {};
	Math::Vector3 m_targetPos = {};

	float m_time=0;

	KdTrailPolygon m_tpoly;

	inline static std::weak_ptr<KdGameObject> s_target;
};