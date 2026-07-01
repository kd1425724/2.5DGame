#include "Player.h"
#include"../../Common/Info/Info.h"
#include"../../Common/Input/Input.h"
#include"../../Scene/SceneManager.h"
#include"../Effect/EffectManager.h"
#include"../../main.h"

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

	auto sceneType = SceneManager::Instance().GetSceneType();

	//タイトルでは自由に動ける
	if (sceneType == SceneManager::SceneType::Title)
	{
		m_damageflg = false;
	}

	m_dashEffectCnt = 0;

	m_jumpBlockModel = m_coremodel;

	m_orbExist = true;
}

void Player::PreUpdate()
{}

void Player::Update()
{
	if (m_shadowflg)return;

	auto sceneType = SceneManager::Instance().GetSceneType();

	//ゲームとリザルト以外では自由に動ける
	if (sceneType == SceneManager::SceneType::Title)
	{
		// 自由移動
		if (Inp.GetPlayerKey(PlayerKeyType::Right))
		{
			m_pos.x += m_speed;
		}
		if (Inp.GetPlayerKey(PlayerKeyType::Left))
		{
			m_pos.x -= m_speed;
		}
	}

	if (Inp.GetDebugKeyDown(DebugKeyType::LKey))
	{
		m_damageflg = !m_damageflg;
	}

	//ポイントライト
	KdShaderManager::Instance().WorkAmbientController().AddPointLight
	(
		{10,0,0},							//色
		3,									//半径
		m_pos	//座標
	);

	

	switch (m_statepattern)
	{
	case Player::PlayerStatePattern::Start:
		break;
	case Player::PlayerStatePattern::Loop:
		if (!m_isground)
		{
			if (Inp.GetPlayerKeyDown(PlayerKeyType::Plunge))
			{
				KdAudioManager::Instance().Play("Asset/Sounds/SE/PlungeSE/PlungeSE.wav");
			}
			if (Inp.GetPlayerKey(PlayerKeyType::Plunge))
			{
				m_gravity += 0.05f;
			}
		}
		//ジャンプ処理
		switch (m_jumppattern)
		{
		case Player::PlayerJumpPattern::None:

			if (Inp.GetPlayerKeyDown(PlayerKeyType::Jump))
			{
				//ジャンプ1段目
				m_gravity = -m_onejumppow;

				//地面から離れた
				m_isground = false;

				KdAudioManager::Instance().Play("Asset/Sounds/SE/JumpSE/JumpSE.wav");
			
				// ジャンプエフェクト
				for (int i = 0; i < 8; i++)
				{
					EffectManager::Instance().CreateSquareEffect(
						m_pos + Math::Vector3(0, -0.5f, 0),
						Math::Vector3(
							KdRandom::GetFloat(-0.15f, 0.15f),
							KdRandom::GetFloat(-0.05f, 0.15f),
							0),
						KdRandom::GetFloat(0.5f, 0.8f),
						20);
				}
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
				KdAudioManager::Instance().Play("Asset/Sounds/SE/JumpSE/JumpSE.wav");

				//オーブ消滅
				m_orbExist = false;
				KdAudioManager::Instance().Play("Asset/Sounds/SE/OrbBreakSE/OrbBreakSE.wav");
				
				
				m_gravity = -m_twojumppow;
				m_jumppattern = PlayerJumpPattern::Jump2;

				// 2段ジャンプエフェクト
				for (int i = 0; i < 10; i++)
				{
					EffectManager::Instance().CreateSquareEffect(
						m_pos,
						Math::Vector3(
							KdRandom::GetFloat(-0.2f, 0.2f),
							KdRandom::GetFloat(-0.2f, 0.2f),
							0),
						KdRandom::GetFloat(0.4f, 0.7f),
						20);
				}

				for (int i = 0; i < 20; i++)
				{
					EffectManager::Instance().CreateSquareEffect(
						m_pos,
						Math::Vector3(
							KdRandom::GetFloat(-0.35f, 0.35f),
							KdRandom::GetFloat(-0.35f, 0.35f),
							KdRandom::GetFloat(-0.1f, 0.1f)),
						KdRandom::GetFloat(0.4f, 0.8f),
						25);
				}
			}
			//m_color = { 0.3,0,0,1 };
			break;
		case Player::PlayerJumpPattern::Jump2:
			//着地したらNoneに戻す
			//当たり判定処理の部分に書いてる
			//m_color = { 0.1,0.1,0.1f,1 };
			break;
		default:
			break;
		}

		//地面から離れているとき回転
		if (!m_isground)
		{
			m_jumprottimer++;
			if (m_jumprottimer > 15)
			{
				m_rot.z -= 5;
			}
		}
		else
		{
			m_color = { 0.5f,0,0,1 };
		}

	
		//重力が0以下（プレイヤーが上昇中）かつJumpキーが離れされたら
		if (m_gravity < 0 && !Inp.GetPlayerKey(PlayerKeyType::Jump))
		{
			//重力を0に
			m_gravity *= 0.4f;
		}

		// 2段ジャンプ可能なら回転
		if (m_jumppattern != PlayerJumpPattern::Jump2)
		{
			m_jumpBlockRot -= 3.0f;

			if (m_jumpBlockRot <= -360.0f)
			{
				m_jumpBlockRot += 360.0f;
			}
		}
		break;
	case Player::PlayerStatePattern::Death:
		//スクロールを止める
		INFO.SetScrollFlg(false);
		//死亡演出
		m_dissolv += 0.02f;
		m_jumpBlockDissolve += 0.02f;
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
	// Jump2なら消す、それ以外なら表示
	float target = (m_jumppattern == PlayerJumpPattern::Jump2) ? 1.0f : 0.0f;

	if (m_jumppattern == PlayerJumpPattern::Jump2)
	{
		m_jumpBlockScale = 1.0f;
	}
	else
	{
		if (m_jumpBlockScale < 1.3f)
		{
			m_jumpBlockScale += 0.04f;
		}
		else
		{
			m_jumpBlockScale -= (m_jumpBlockScale - 1.0f) * 0.2f;
		}
	}

	const float speed = 0.05f;

	if (m_jumpBlockDissolve < target)
	{
		m_jumpBlockDissolve += speed;

		if (m_jumpBlockDissolve > target)
			m_jumpBlockDissolve = target;
	}
	else if (m_jumpBlockDissolve > target)
	{
		m_jumpBlockDissolve -= speed;

		if (m_jumpBlockDissolve < target)
			m_jumpBlockDissolve = target;
	}


	float dt = Application::Instance().GetDeltaTime();

	m_afterImageTimer += dt;

	if (m_afterImageTimer >= m_afterImageInterval)
	{
		//if (m_jumppattern != PlayerJumpPattern::Jump2)
		{
			m_afterImageTimer = 0.0f;

			AfterImage img;

			Math::Vector3 scroll = { INFO.GetScrollSpeed(),0,0 };
			Math::Matrix scale = Math::Matrix::CreateScale(0.5f * m_jumpBlockScale);
			Math::Matrix mtrans = Math::Matrix::CreateTranslation(m_mWorld.Translation());
			img.mat = scale * mtrans;
			img.alpha = 1.0f;
			img.life = 150.0f;    // 約30フレーム

			m_afterImages.push_front(img);
		}

		if (m_afterImages.size() > 15)
			m_afterImages.pop_back();

	}
	
	// フェード
	
	for (auto it = m_afterImages.begin(); it != m_afterImages.end();)
	{
		it->time += dt;

		// αを時間から計算
		it->alpha = 1.0f - (it->time / it->life);
		if (it->alpha < 0.0f) it->alpha = 0.0f;

		it->mat *= Math::Matrix::CreateTranslation({ -INFO.GetScrollSpeed(), 0, 0 });

		if (it->time >= it->life)
		{
			it = m_afterImages.erase(it);
		}
		else
		{
			++it;
		}
	}

	//重力処理前に保存
	m_prevGravity = m_gravity;

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
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_coremodel, m_mWorld,m_color);
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolv);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);


	DrawJumpBlock();
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
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_coremodel, m_mWorld, m_color);

	//if (m_jumppattern != PlayerJumpPattern::Jump2)
	{
		DrawJumpBlock();
	}

	// コア残像
	for (auto& img : m_afterImages)
	{
		Math::Color color = { 1,0,0,img.alpha };

		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_coremodel, img.mat,color);
	}
}

void Player::DrawJumpBlock()
{
	float radius = 1.3f;

	for (int i = 0; i < 4; i++)
	{
		float angle = DirectX::XMConvertToRadians(
			m_jumpBlockRot + i * 90.0f);

		Math::Vector3 pos = { 0,0,-2 };

		Math::Matrix world =
			Math::Matrix::CreateScale(0.3f) *
			Math::Matrix::CreateTranslation(0, 0, -radius) *
			Math::Matrix::CreateRotationY(angle) *
			Math::Matrix::CreateTranslation(m_pos);

		Math::Color color;

		if (m_jumppattern != PlayerJumpPattern::Jump2)
		{
			// 使用可能：明るく発光
			color = { 3.0f,0.3f,0.3f,1.0f };
		}
		else
		{
			// 使用済み：暗い
			color = { 0.8f,0.1f,0.1f,1.0f };
		}

		KdShaderManager::Instance().m_StandardShader.SetDissolve(m_jumpBlockDissolve);
		KdShaderManager::Instance().m_StandardShader.DrawModel(
			*m_jumpBlockModel,
			world,
			color);
	}

	KdShaderManager::Instance().m_StandardShader.SetDissolve(0.0f);
}


void Player::Hit()
{
	MatrixUpdate();

	// 移動前の基準Y（今フレームで実際に落下した量を遡る）
	float fallDistance = m_prevGravity; // 実際に落ちた量

	//プレイヤー座標調整地面判定用（プレイヤーの足元）
	float rayPosX[3] =
	{
		-0.28f,    // 左足
		 0.0f,     // 中央
		 0.28f     // 右足
	};
	float groundpossurplusY = -0.5f;

	float maxOverLap = 0;
	Math::Vector3 hitPos;
	bool hit = false;
	float hitRayOffsetX = 0.0f;

	//レイ判定
	std::list<KdCollider::CollisionResult> retRayList;

	for (int i = 0; i < 3; i++)
	{
		retRayList.clear();

		KdCollider::RayInfo ray;

		ray.m_pos = m_pos;
		ray.m_pos.x += rayPosX[i];
		ray.m_pos.y += groundpossurplusY;

		float enableStepHigh = 0.1f;
		// 移動前の高さまでさかのぼる
		ray.m_pos.y += fallDistance;     // ここを enableStepHigh ではなく実移動量で戻す
		ray.m_pos.y += enableStepHigh;   // 段差用の余白として少し追加

		ray.m_dir = { 0,-1,0 };
		ray.m_dir.Normalize();

		ray.m_range = m_gravity + enableStepHigh;
		ray.m_type = KdCollider::TypeGround;

		// デバッグ表示
		//m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(ray, &retRayList);
		}

		for (auto& ret : retRayList)
		{
			Math::Vector3 normal = ret.m_hitNDir;
			normal.Normalize();

			// 上向きの面だけ地面とする
			if (normal.y < 0.8f)
			{
				continue;
			}

			if (maxOverLap < ret.m_overlapDistance)
			{
				maxOverLap = ret.m_overlapDistance;
				hitPos = ret.m_hitPos;
				hitRayOffsetX = rayPosX[i]; 
				hit = true;
			}
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
			m_jumprottimer = 0;

			//オーブがなければ再生
			if (!m_orbExist)
			{
				m_orbExist = true;
				KdAudioManager::Instance().Play("Asset/Sounds/SE/OrbReturnSE/OrbReturnSE.wav");
			}
			// 強く落下していたら着地エフェクト
			if (m_prevGravity > 0.4f) 
			{

				KdAudioManager::Instance().Play("Asset/Sounds/SE/LandingSE/LandingSE.wav");
				for (int i = 0; i < 12; i++)
				{
					EffectManager::Instance().CreateSquareEffect(
						m_pos + Math::Vector3(0, -0.5f, 0),
						Math::Vector3(
							KdRandom::GetFloat(-0.10, 0.25f),
							KdRandom::GetFloat(-0.05f, 0.2f),
							0),
						KdRandom::GetFloat(1.3f, 1.6f),
						25);
				}
			}
		}
		//回転初期化
		m_rot.z = 0;
		//			   ↓余剰分を反転させる
		m_pos = hitPos -= Math::Vector3(hitRayOffsetX, groundpossurplusY, 0);
		m_gravity = 0;

		if (!m_shadowflg)
		{
			//ダッシュエフェクト
			if (INFO.GetScrollFlg())
			{
				m_dashEffectCnt++;

				if (m_dashEffectCnt > 2)
				{
					m_dashEffectCnt = 0;

					EffectManager::Instance().CreateSquareEffect(
						m_pos +
						Math::Vector3(0, -0.5f, 0),
						Math::Vector3(KdRandom::GetFloat(-0.2, -0.1f), KdRandom::GetFloat(0.0f, 0.15f), 0),
						KdRandom::GetFloat(0.2f, 0.4f),
						20);
				}
			}
		}
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
		sphere.m_sphere.Radius = 0.49f;
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
		bool shit = false;
		//当たった方向を格納する変数
		Math::Vector3 hitDir;

		for (auto& ret : retSphereList)
		{
			//当たったTypeがイベントなら飛ばす
			if (ret.m_hitType & KdCollider::TypeEvent)continue;

			//ダメージTypeに当たったら
			if (ret.m_hitType & KdCollider::TypeDamage)
			{
				if (m_damageflg)
				{
					KdAudioManager::Instance().Play("Asset/Sounds/SE/DeathSE/DeathSE.wav",false);
					//死亡
					m_statepattern = PlayerStatePattern::Death;
					//画面揺れ開始
					SceneManager::Instance().GetCamera()->StartShake(0.3f, 20);
					return;
				}
			}
		
			if (ret.m_hitType & KdCollider::TypeGround)
			{
				//球にめり込んだ長さが一番長いものを探す
				if (maxOverLap < ret.m_overlapDistance)
				{
					//更新
					maxOverLap = ret.m_overlapDistance;
					hitDir = ret.m_hitDir;
					shit = true;
				}
			}
		}

		if (shit)
		{
			//if (hit)return;

			hitDir.Normalize();

			if (m_gravity < 0 && hitDir.y < -0.5f)
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
				if (m_damageflg)
				{
					KdAudioManager::Instance().Play("Asset/Sounds/SE/DeathSE/DeathSE.wav",false);
					// 左から当たった
					m_statepattern = PlayerStatePattern::Death;
					//画面揺れ開始
					SceneManager::Instance().GetCamera()->StartShake(0.3f, 20);
					return;
				}
			}

			//Z方向への押し戻し無効
			hitDir.z = 0;
			
			//正規化（長さ１にする）
			hitDir.Normalize();
			m_pos += hitDir * (maxOverLap);
		}

		MatrixUpdate();
	}

	//奈落判定
	if (m_pos.y < INFO.AbyssJudgmentPos)
	{
		if (m_damageflg)
		{
			KdAudioManager::Instance().Play("Asset/Sounds/SE/DeathSE/DeathSE.wav", false);
			//死亡
			m_statepattern = PlayerStatePattern::Death;
			//画面揺れ開始
			SceneManager::Instance().GetCamera()->StartShake(0.3f, 20);
			return;
		}
	}
}

void Player::PlayerDataLoad()
{
	FILE* fp=nullptr;

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

