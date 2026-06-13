#include "Coin.h"
#include"../../../Manager/ScoreManager/ScoreManager.h"
void Coin::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Object/Stage/Block/Block.gltf");
}

void Coin::Update()
{
	//BaseItem::Update();

	//アニメーション
	m_rot += 0.1f;
	Math::Matrix mrot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rot));
	m_mWorld = mrot * Scroll();
}

void Coin::DrawLit()
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


		//エフェクト発生（未実装）


		//スコアアップ
		int upval = 100;
		SCOREMANAGER.ScoreUp(upval);
	

		//消滅
		m_isExpired = true;
	}
}
