#include "RoomExit.h"
#include"../../../Manager/StageManager/StageManager.h"
void RoomExit::Init()
{
	DirectX::BoundingBox box;
	box.Center = m_pos;
	box.Extents = { 1,1,1 }*m_scale / 2; // 半サイズ

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape(
		"RoomExit",
		box,
		KdCollider::TypeEvent
	);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void RoomExit::OnHit(KdGameObject* _other)
{
	//プレイヤーと当たった時
	if (_other->GetObjectTag() == ObjectTag::Player)
	{
		//部屋更新
		STAGEMANAGER.ChangeRoom();

		//消去
		m_isExpired = true;
	}
}
