#include "Goal.h"
#include"../../../Common/Info/Info.h"

void Goal::Init()
{
	DirectX::BoundingBox box;
	box.Center = m_pos;
	box.Extents = { 1,1,1 };//m_scale / 2; // 半サイズ

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape(
		"RoomGoal",
		box,
		KdCollider::TypeEvent
	);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Goal::OnHit(KdGameObject* _other)
{
	//プレイヤーと当たったら
	if (_other->GetObjectTag() == ObjectTag::Player)
	{
		//サウンド（未実装）

		//ゴール
		INFO.SetGoalFlg(true);

		//消滅
		m_isExpired = true;
	}
}
