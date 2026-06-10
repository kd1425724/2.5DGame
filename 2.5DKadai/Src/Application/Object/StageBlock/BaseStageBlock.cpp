#include "BaseStageBlock.h"
#include"../../Common/Info/Info.h"

void BaseStageBlock::Init()
{
	//モデルデータ入ってなかったら処理しない
	if (!m_model)return;

	m_name = "Block";

	//当たり判定の設定
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定
	m_pCollider->RegisterCollisionShape
	(
		"BlockCollision",
		m_model,
		KdCollider::TypeGround
	);
}

void BaseStageBlock::Update()
{
	m_pos.x -= INFO.GetScrollSpeed();

	Math::Matrix mtrans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = mtrans;
}

void BaseStageBlock::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
