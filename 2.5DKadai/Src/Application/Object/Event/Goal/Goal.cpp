#include "Goal.h"
#include"../../../Common/Info/Info.h"

void Goal::Init()
{
	m_scale = { 1,7,1 };

	m_model = std::make_shared<KdModelData>();
	m_model = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Object/Stage/Block/Block.gltf");

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

	m_hitflg = true;
}

void Goal::Update()
{
	m_rot.y += 2.0f;

	Scroll();

	MatrixUpdate();
}

void Goal::DrawLit()
{
	Math::Color color = { 0,0,1.0f,1.0f };
	//ブレンディング方法を変える								↓加算
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Add);

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld,color);

	//表示し終わったら元に戻す
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Alpha);
	

}

void Goal::OnHit(KdGameObject* _other)
{
	if (!m_hitflg)return;

	//プレイヤーと当たったら
	if (_other->GetObjectTag() == ObjectTag::Player)
	{
		//サウンド
		KdAudioManager::Instance().Play("Asset/Sounds/SE/GoalSE/GoalSE.wav", false);
		//ゴール
		INFO.SetGoalFlg(true);

		//当たり判定消失
		m_hitflg = false;
	}
}
