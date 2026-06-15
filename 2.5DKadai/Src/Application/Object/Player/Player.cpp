#include "Player.h"
#include"../../Common/Info/Info.h"
#include"../../Common/Input/Input.h"
#include"../../Scene/SceneManager.h"
#include"../Effect/EffectManager.h"

void Player::Init()
{
	m_name = "Player";

	//デバッグ用のポインタを実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Object/Player/Player.gltf");

	m_coremodel = std::make_shared<KdModelData>();
	m_coremodel->Load("Asset/Models/Object/Player/PlayerCore/PlayerCore.gltf");
	
	//座標
	m_pos = { -4,-4,0 };
	//移動スピード
	m_speed = 0.2f;
	//サイズ
	m_scale = { 1,1,1 };

	m_move = { 1,0,0 };

	m_shadowflg = false;
}

void Player::PreUpdate()
{}

void Player::Update()
{
	if (m_shadowflg)return;

	//ポイントライト
	KdShaderManager::Instance().WorkAmbientController().AddPointLight
	(
		{ 10,0,0 },							//色
		3,									//半径
		m_pos	//座標
	);

	switch (m_statepattern)
	{
	case Player::PlayerStatePattern::Start:
		break;
	case Player::PlayerStatePattern::Loop:

		/*m_move.Normalize();
		m_pos += m_move * m_speed;*/

		//ジャンプ処理
		switch (m_jumppattern)
		{
		case Player::PlayerJumpPattern::None:
			
			if (Inp.GetPlayerKeyDown(PlayerKeyType::Jump))
			{
				//ジャンプ1段目
				m_gravity = -m_onejumppow;

				//エフェクト
				EFFECT.CreateEffect("PlayerJump", {0,0,0});

				//地面から離れた
				m_isground = false;
			}
			if (!m_isground)
			{
				//地面から離れてたらJump1に移行
				m_jumppattern = PlayerJumpPattern::Jump1;
			}
			break;
		case Player::PlayerJumpPattern::Jump1:
			if (Inp.GetPlayerKeyDown(PlayerKeyType::Jump))
			{
				//ジャンプ2段目
				m_gravity = -m_twojumppow;
				m_jumppattern = PlayerJumpPattern::Jump2;
			}
			break;
		case Player::PlayerJumpPattern::Jump2:
			//着地したらNoneに戻す
			//当たり判定処理の部分に書いてる
			break;
		default:
			break;
		}

		//地面から離れているとき回転
		if (!m_isground)
		{
			m_rot.z -= 5;
		}

		if (Inp.GetPlayerKey(PlayerKeyType::Plunge))
		{
			m_gravity += 0.05f;
		}

		//重力が0以下（プレイヤーが上昇中）かつJumpキーが離れされたら
		if (m_gravity < 0 && Inp.GetPlayerKeyUp(PlayerKeyType::Jump))
		{
			//重力を0に
			m_gravity = 0;
		}

		//switch (m_attackpattern)
		//{
		//case Player::PlayerAttackPattern::None:
		//	if (Inp.GetPlayerKeyDown(PlayerKeyType::Attack))
		//	{
		//		m_attackpattern = PlayerAttackPattern::Attack1;

		//		//通常攻撃1段目用アニメーション設定
		//		//UVRectControl(PlayerAnimeType::Attack1, [this]()
		//		//	{
		//		//		//1段目攻撃が終わったら（アニメーションが終わったら）待機状態に
		//		//		m_attackpattern = PlayerAttackPattern::Standby;

		//		//		//待機時間
		//		//		m_standbytime = StandbyTime;
		//		//	});
		//	}
		//	break;
		//case Player::PlayerAttackPattern::Attack1:
		//	if (Inp.GetPlayerKeyDown(PlayerKeyType::Attack))
		//	{
		//		//入力保存
		//		m_inputkeep = true;
		//	}

		//	break;
		//case Player::PlayerAttackPattern::Attack2:
		//	break;
		//case Player::PlayerAttackPattern::Standby:
		//	//既に入力されているか、待機状態中に入力したら
		//	if (m_inputkeep || Inp.GetPlayerKeyDown(PlayerKeyType::Attack))
		//	{
		//		//2段目攻撃
		//		m_attackpattern = PlayerAttackPattern::Attack2;

		//		//アニメーション
		//		UVRectControl(PlayerAnimeType::Attack2, [this]()
		//			{
		//				//2段目攻撃が終わったらNoneに戻す
		//				m_attackpattern = PlayerAttackPattern::None;
		//				//入力保存用falseに
		//				m_inputkeep = false;

		//			});
		//	}
		//	//待機状態が終了したらNoneに戻す
		//	m_standbytime--;
		//	if (m_standbytime <= 0)
		//	{
		//		m_attackpattern = PlayerAttackPattern::None;
		//	}

		//	break;
		//default:
		//	break;
		//}

		////スキル処理
		//if (Inp.GetPlayerKeyDown(PlayerKeyType::Skill))
		//{
		//	UVRectControl(PlayerAnimeType::spDash);
		//	//スキル発動時通常攻撃のpatternをNoneに
		//	m_attackpattern = PlayerAttackPattern::None;
		//}

		break;
	case Player::PlayerStatePattern::Death:
		//スクロールを止める
		INFO.SetScrollFlg(false);
		//死亡演出
		m_dissolv += 0.02f;
		if (m_dissolv > 1.0f)
		{
			m_isExpired = true;
			return;
		}
		break;
	default:
		break;
	}



	if (m_statepattern == PlayerStatePattern::Death)return;

	m_afterImageTimer += 1.0f;

	if (m_afterImageTimer >= m_afterImageInterval)
	{
		m_afterImageTimer = 0.0f;

		AfterImage img;

		Math::Vector3 scroll = { INFO.GetScrollSpeed(),0,0 };
		Math::Matrix scale = Math::Matrix::CreateScale(0.7f);
		Math::Matrix mtrans = Math::Matrix::CreateTranslation(m_mWorld.Translation());
		img.mat = scale * mtrans;
		img.offset = scroll;
		img.alpha = 1.0f;

		m_afterImages.push_front(img);

		if (m_afterImages.size() > 15)
			m_afterImages.pop_back();
	}

	// フェード
	for (auto& img : m_afterImages)
	{
		img.alpha -= 0.005f;
		img.mat *= Math::Matrix::CreateTranslation(-img.offset);
	}

	//前回のm_gravityの値を保存
	float prevgravity = m_gravity;

	//重力処理
	m_pos.y -= m_gravity;
	m_gravity += m_gravitysubtractionvalue;

	//行列
	MatrixUpdate();
}

void Player::PostUpdate()
{
	if (!m_shadowflg)
	{
		// 削除
		m_afterImages.erase(
			std::remove_if(m_afterImages.begin(), m_afterImages.end(),
				[](const AfterImage& a)
				{
					return a.alpha <= 0.0f;
				}),
			m_afterImages.end());
	}

	//死亡演出中処理しない
	if (m_statepattern == PlayerStatePattern::Death)return;

	Hit();
}

void Player::DrawLit()
{
	if (m_shadowflg)return;
	//ディゾルブ											↓０～１
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolv);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_coremodel, m_mWorld);
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolv);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Player::GenerateDepthMapFromLight()
{
	if (m_shadowflg)return;
		//ディゾルブ											↓０～１
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolv);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Player::DrawBright()
{
	if (m_shadowflg)return;
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolv);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_coremodel, m_mWorld);

	// コア残像
	for (auto& img : m_afterImages)
	{
		Math::Color color = { 1,0.1,0.1,img.alpha };

		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_coremodel, img.mat, color);
	}

}


void Player::Hit()
{
	//プレイヤー座標調整地面判定用（プレイヤーの足元）
	float groundpossurplusX = 0;
	float groundpossurplusY = -0.5f;

	//レイ判定
	KdCollider::RayInfo ray;
	//レイの設定
	ray.m_pos = m_pos;
	ray.m_pos.y += groundpossurplusY;
	ray.m_pos.x += groundpossurplusX;
	float enableStepHigh = 0.3f;
	ray.m_pos.y += enableStepHigh;
	ray.m_dir = { 0,-1,0 };
	ray.m_dir.Normalize();
	ray.m_range = m_gravity +enableStepHigh;
	ray.m_type = KdCollider::TypeGround;

	//デバッグ
	//m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	//レイに当たったオブジェクトを格納
	std::list<KdCollider::CollisionResult> retRayList;
	//当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retRayList);
	}

	//レイに当たったリストから一番近いオブジェクトを探す
	float maxOverLap = 0;
	Math::Vector3 hitPos;
	bool hit = false;

	for (auto& ret : retRayList)
	{
		//レイを遮断しオーバーした長さが一番長いものを探す
		//上回っていたら更新
		if (maxOverLap < ret.m_overlapDistance)
		{
			//更新
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}
	//当たったら
	if (hit)
	{
		//着地した瞬間のみ実行
		if (!m_isground)
		{
			m_isground = true;
			m_jumppattern = PlayerJumpPattern::None;

		}
		//回転初期化
		m_rot.z = 0;
		//			   ↓余剰分を反転させる
		m_pos = hitPos -= Math::Vector3(groundpossurplusX, groundpossurplusY, 0);
		m_gravity = 0;
	}
	else
	{
		m_isground = false;
	}

	//球（スフィア）判定地面との当たり判定
	{
		//プレイヤー座標調整壁判定用（プレイヤーの中心）
		float spherepossurplusX = 0;
		float spherepossurplusY = 0;

		//球判定の設定
		KdCollider::SphereInfo sphere;
		sphere.m_sphere.Center = m_pos;
		sphere.m_sphere.Center.y += spherepossurplusY;
		sphere.m_sphere.Center.x += spherepossurplusX;
		sphere.m_sphere.Radius = 0.50f;
		sphere.m_type = KdCollider::TypeGround | KdCollider::TypeEvent|KdCollider::TypeDamage;

		//デバッグ
		//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

		//球に当たったオブジェクト情報を格納するリスト
		std::list<KdCollider::CollisionResult> retSphereList;

		//全オブジェクトと当たり判定を行う
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			//球と当たり判定
			if (obj->Intersects(sphere, &retSphereList))
			{
				obj->OnHit(this);
			}
		}

		//球に当たったリストから一番近いオブジェクトを探す
		maxOverLap = 0; //球の時はめりこんだ長さ
		hit = false;
		//当たった方向を格納する変数
		Math::Vector3 hitDir;

		for (auto& ret : retSphereList)
		{
			//当たったTypeがイベントなら飛ばす
			if (ret.m_hitType & KdCollider::TypeEvent)continue;

			//ダメージTypeに当たったら
			if (ret.m_hitType & KdCollider::TypeDamage)
			{
				//死亡
				m_statepattern = PlayerStatePattern::Death;
				//画面揺れ開始
				SceneManager::Instance().GetCamera()->StartShake(0.3f, 20);
				return;
			}
			//球にめり込んだ長さが一番長いものを探す
			if (maxOverLap < ret.m_overlapDistance)
			{
				//更新
				maxOverLap = ret.m_overlapDistance;
				hitDir = ret.m_hitDir;
				hit = true;
			}
		}

		if (hit)
		{
			hitDir.Normalize();

			if (hitDir.y < -0.5f)
			{
				// 下から当たった
				m_gravity = 0;
			}
			else if (hitDir.y > 0.5f)
			{
				//上から当たった
				//何もしない
			}
			else if (hitDir.x < -0.5f)
			{
				// 左から当たった
				m_statepattern = PlayerStatePattern::Death;
				//画面揺れ開始
				SceneManager::Instance().GetCamera()->StartShake(0.3f, 20);
				return;
			}

			//Z方向への押し戻し無効
			hitDir.z = 0;
			//正規化（長さ１にする）
			hitDir.Normalize();
			m_pos += hitDir * maxOverLap;
		}
	}

	//奈落判定
	if (m_pos.y < INFO.AbyssJudgmentPos)
	{
		//死亡
		m_statepattern = PlayerStatePattern::Death;
		//画面揺れ開始
		SceneManager::Instance().GetCamera()->StartShake(0.3f, 20);
		return;
	}
}

void Player::PlayerDataLoad()
{
	FILE* fp;

	if (fopen_s(&fp, "Asset/Data/ObjectData/PlayerData/PlayerData.csv", "r") == 0)
	{
		char dummy[255];

		//画像座標
		Math::Vector3 pos = {};

		//アニメーション
		int animid = 0;


		fgets(dummy, 255, fp);		//1行飛ばす

		//読み込む
		fscanf_s(fp, "%*[^,],%f,%f", &pos.x, &pos.y);

		//代入
		m_pos = pos;

		fclose(fp);
	}
}

