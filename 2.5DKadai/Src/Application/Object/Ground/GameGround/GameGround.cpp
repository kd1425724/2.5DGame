#include "GameGround.h"

void GameGround::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Object/Ground/testblock/testblock.gltf");

	//当たり判定の設定
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定
	m_pCollider->RegisterCollisionShape
	(
		"GroundCollision",
		m_model,
		KdCollider::TypeGround
	);
}

void GameGround::Update()
{

}

void GameGround::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
