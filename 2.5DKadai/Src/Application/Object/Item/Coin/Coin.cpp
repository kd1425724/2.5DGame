#include "Coin.h"
#include"../../../Manager/ScoreManager/ScoreManager.h"
#include"../../Effect/EffectManager.h"
#include"../../Effect/BaseEffect.h"
void Coin::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Object/Coin/Coin.gltf");
	
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
	if (m_hitflg&&!m_getflg)
	{
		Scroll();
	}

	if (m_getflg)
	{
		Math::Matrix mat = Math::Matrix::CreateScale(0.4f, 0.4f, 0.4f) * m_mWorld;
		m_tpoly.AddPoint(mat);

		Math::Vector3 toTarget = m_targetPos - m_pos;
		float dist = toTarget.Length();

		float speed = m_time;

		if (m_time >= 1.0f)
		{
			speed = 1.0f;
		}

		if (dist <= speed)
		{
			SCOREMANAGER.CoinUp();

			//エフェクト発生
			EFFECT.CreateEffect("CoinGet", m_targetPos+Math::Vector3(2,-1,-2), eBright);

			m_pos = m_targetPos;
			m_isExpired = true;
			return;
		}
		Math::Vector3 dir = toTarget;
		dir.Normalize();

		m_time += 0.07f;

		if (m_time > 1)
		{
			m_time = 1;

			m_pos += dir * 1.0f;

			MatrixUpdate();
			return;
		}


		m_moveDir = Math::Vector3::Lerp(m_moveDir, dir, 0.08f);
		m_moveDir.Normalize();

		// 距離が近いほど減速
		speed = m_time;

		m_pos += m_moveDir * speed;

		MatrixUpdate();
		return;
	}

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
	if (!m_hitflg)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Coin::DrawBright()
{
	if (!m_getflg)return;

	Math::Color color = { 1,1,0,0.1f };
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_tpoly,Math::Matrix::Identity,color);
}


void Coin::OnHit(KdGameObject * other)
{
	if (!m_hitflg)return;
	if (m_getflg)return;

	//プレイヤーと当たったら
	if (other->GetObjectTag() == ObjectTag::Player)
	{

		//サウンド
		KdAudioManager::Instance().Play("Asset/Sounds/SE/CoinGetSE/CoinGetSE.wav", false);

		//エフェクト発生
		EFFECT.CreateEffect("CoinGet", m_pos, eBright | eScroll);

		//スコアアップ
		int upval = 100;
		SCOREMANAGER.ScoreUp(upval);

		//取得演出へ
		m_getflg = true;
		m_getTime = 0.0f;

		m_moveDir = Math::Vector3(0, 0, -0.1f);
		//m_moveDir.Normalize();

		// UIのコイン表示のワールド座標
		if (!s_target.expired())
		{
			auto t = s_target.lock();

			m_targetPos = t->GetPos();

			//z情報無効
			m_targetPos.x -= 2;
			m_targetPos.y += 1;
			m_targetPos.z = 0;
		}
		else
		{
			m_isExpired = true;
		}
	}
}
