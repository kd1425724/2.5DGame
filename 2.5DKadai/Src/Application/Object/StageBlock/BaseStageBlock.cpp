#include "BaseStageBlock.h"
#include"../../Common/Info/Info.h"

// staticメンバ変数の実体化
std::unordered_map<std::string, std::shared_ptr<KdModelData>>
BaseStageBlock::s_modelTable;

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

	MatrixUpdate();
}

void BaseStageBlock::DrawLit()
{
	Math::Color color = { 1,1,1,1 }; 
	if(!m_hitflg)
	{ 
		color = { 0.6,0.6,0.6,1 };
	}
	
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, color);
}

void BaseStageBlock::GenerateDepthMapFromLight()
{
	
}

void BaseStageBlock::OnHit(KdGameObject* _other)
{
	//プレイヤーと当たったら
	//左右からあたったときのみ通る
	if (_other->GetObjectTag() == ObjectTag::Player)
	{
		
	}
}
