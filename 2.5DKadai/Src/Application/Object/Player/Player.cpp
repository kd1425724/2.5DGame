#include "Player.h"
#include"../../Common/Info/Info.h"
#include"../../Common/Input/Input.h"
#include"../../Scene/SceneManager.h"

void Player::Init()
{
	m_name = "Player";

	//デバッグ用のポインタを実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Object/Stage/Block/Block.gltf");
	
	//座標
	m_pos = { 0,0 };
	//移動スピード
	m_speed = 0.2f;
	//サイズ
	m_scale = { 1,1,1 };

	m_move = { 1,0,0 };
}

void Player::PreUpdate()
{}

void Player::Update()
{
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
				m_jumppattern = PlayerJumpPattern::Jump1;
				//UVRectControl(PlayerAnimeType::Jump);

				//地面から離れた
				m_isground = false;
			}
			break;
		case Player::PlayerJumpPattern::Jump1:
			if (Inp.GetPlayerKeyDown(PlayerKeyType::Jump))
			{
				//ジャンプ2段目
				m_gravity = -m_twojumppow;
				m_jumppattern = PlayerJumpPattern::Jump2;
			}
			m_rot.z -= 5;

			break;
		case Player::PlayerJumpPattern::Jump2:
			//着地したらNoneに戻す
			//当たり判定処理の部分に書いてる
			m_rot.z -= 5;
			break;
		default:
			break;
		}

		if (m_gravity < 0 && Inp.GetPlayerKeyUp(PlayerKeyType::Jump))
		{
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
		//死亡演出
		m_isExpired = true;
		break;
	default:
		break;
	}

	//前回のm_gravityの値を保存
	float prevgravity = m_gravity;

	//重力処理
	m_pos.y -= m_gravity;
	m_gravity += m_gravitysubtractionvalue;

	//地面から離れている間
	if (!m_isground)
	{
		//落下が始まった瞬間のみ実行
		if (prevgravity <= 0 && m_gravity > 0)
		{
			//UVRectControl(PlayerAnimeType::Fall);
		}
	}

	//行列
	MatrixUpdate();
}

void Player::PostUpdate()
{
	//死亡演出中処理しない
	if (m_statepattern == PlayerStatePattern::Death)return;

	Hit();
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
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
	float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;
	ray.m_dir = { 0,-1,0 };
	ray.m_dir.Normalize();
	ray.m_range = m_gravity +enableStepHigh;
	ray.m_type = KdCollider::TypeGround;

	//デバッグ
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

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
		sphere.m_sphere.Radius = 0.5f;
		sphere.m_type = KdCollider::TypeGround | KdCollider::TypeEvent;

		//デバッグ
		m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

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

			// 当たった方向
			Math::Vector3 dir = ret.m_hitDir;

			// 左右から当たった
			//xの方が大きければ　abs...絶対値
			if (abs(dir.x) > abs(dir.y))
			{
				//死亡演出へ
				m_statepattern = PlayerStatePattern::Death;

				//スクロール停止
				INFO.SetScrollFlg(false);
				return;
			}
			if (dir.y < 0)
			{
				// 下から当たった
				m_gravity = 0;
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
			//Z方向への押し戻し無効
			hitDir.z = 0;
			//正規化（長さ１にする）
			hitDir.Normalize();

			//押し戻し
			m_pos += hitDir * maxOverLap;
		}
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

