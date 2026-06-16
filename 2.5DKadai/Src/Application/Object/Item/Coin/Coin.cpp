#include "Coin.h"
#include"../../../Manager/ScoreManager/ScoreManager.h"
#include"../../Effect/EffectManager.h"
void Coin::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Object/Coin/Coin.gltf");
	/*if (!s_model)
	{
		m_model = std::make_shared<KdModelData>();
		m_model->Load("Asset/Models/Object/Coin/Coin.gltf");
	}*/
	
	//m_model = s_model;
	//モデルデータ入ってなかったら処理しない
	if (!m_model)return;

	m_name = "Coin";

	//当たり判定の設定
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定
	m_pCollider->RegisterCollisionShape
	(
		"CoinCollision",
		m_model,
		KdCollider::TypeEvent
	);
}

void Coin::Update()
{
	//BaseItem::Update();

	Scroll();
	//アニメーション
	m_rot.y += 1.5f;
	MatrixUpdate();
}

void Coin::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Coin::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Coin::OnHit(KdGameObject * other)
{
	//プレイヤーと当たったら
	if (other->GetObjectTag() == ObjectTag::Player)
	{
		//取得
		SCOREMANAGER.CoinUp();

		//サウンド（未実装）


		//エフェクト発生
		EFFECT.CreateEffect("CoinGet", m_pos);

		//スコアアップ
		int upval = 100;
		SCOREMANAGER.ScoreUp(upval);
	

		//消滅
		m_isExpired = true;
	}
}
