#include "Player.h"
#include"../../Common/Input/Input.h"
#include"../../Scene/SceneManager.h"

void Player::Init()
{
	//デバッグ用のポインタを実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/GameScene/Player/Player.png");
	
	//画像原点
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetScale(5);

	//画像分割
	//Math::Vector2 uvrect = { 14,8 };
	Math::Vector2 uvrect = { 12,15 };
	m_polygon->SetSplit(uvrect.x, uvrect.y);

	m_polygon->SetUVRect(0);


	//座標
	m_pos = {0,30};
	//移動スピード
	m_speed = 0.3f;
	//サイズ
	m_scale = { 1,1,1 };

	m_move = { 1,0,0 };

	//アニメーションIDロード
	PlayerDataLoad();

	//通常アニメーション
	UVRectControl(PlayerAnimeType::Dash);
}

void Player::PreUpdate()
{}

void Player::Update()
{
	static Math::Vector3 move = {};
	move = {};
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		move.x = 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		move.x = -1.0f;
	}
	move.Normalize();
	m_pos += move * m_speed;

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
			if (Inp.GetPlayerKey(PlayerKeyType::Jump) && Inp.GetPlayerKeyDown(PlayerKeyType::Jump))
			{
				//ジャンプ1段目
				m_gravity = -m_onejumppow;
				m_jumppattern = PlayerJumpPattern::Jump1;
				UVRectControl(PlayerAnimeType::Jump);

				//地面から離れた
				m_isground = false;
			}
			break;
		case Player::PlayerJumpPattern::Jump1:
			if (Inp.GetPlayerKey(PlayerKeyType::Jump) && Inp.GetPlayerKeyDown(PlayerKeyType::Jump))
			{
				//ジャンプ2段目
				m_gravity = -m_twojumppow;
				m_jumppattern = PlayerJumpPattern::Jump2;
				UVRectControl(PlayerAnimeType::Jump);
			}
			break;
		case Player::PlayerJumpPattern::Jump2:
			//着地したらNoneに戻す
			//当たり判定処理の部分に書いてる
			break;
		default:
			break;
		}

		switch (m_attackpattern)
		{
		case Player::PlayerAttackPattern::None:
			if (Inp.GetPlayerKey(PlayerKeyType::Attack) && Inp.GetPlayerKeyDown(PlayerKeyType::Attack))
			{
				m_attackpattern = PlayerAttackPattern::Attack1;

				//通常攻撃1段目用アニメーション設定

				//UVRectControl();
			}
			break;
		case Player::PlayerAttackPattern::Attack1:
			if (Inp.GetPlayerKey(PlayerKeyType::Attack) && Inp.GetPlayerKeyDown(PlayerKeyType::Attack))
			{
				m_inputkeep = true;
			}
			//1段目攻撃が終わったら（アニメーションが終わったら）待機状態に

			
			break;
		case Player::PlayerAttackPattern::Attack2:
			break;
		case Player::PlayerAttackPattern::Standby:
			//既に入力されているか、待機状態中に入力したら
			if (m_inputkeep ||!Inp.GetPlayerKey(PlayerKeyType::Attack) && Inp.GetPlayerKeyDown(PlayerKeyType::Attack))
			{
				m_attackpattern = PlayerAttackPattern::Attack2;
			}
			//待機状態が終了したらNoneに戻す
			m_standbytime--;
			if (m_standbytime <= 0)
			{
				m_attackpattern = PlayerAttackPattern::None;
			}

			break;
		default:
			break;
		}

		//スキル処理
		if (!Inp.GetPlayerKey(PlayerKeyType::Skill) && Inp.GetPlayerKeyDown(PlayerKeyType::Skill))
		{
			
		}

		//ループ中行動パターン
		switch (m_looppattern)
		{
		case Player::PlayerLoopPattern::None:
			
			break;
		case Player::PlayerLoopPattern::SpDash:

			//スキル処理

			break;
		default:
			break;
		}


		break;
	case Player::PlayerStatePattern::Death:
		break;
	default:
		break;
	}

	//前回のm_gravityの値を保存
	float prevgravity = m_gravity;

	//重力処理
	m_pos.y -= m_gravity;
	m_gravity += m_gravitysubtractionValue;

	//地面から離れている間
	if (!m_isground)
	{
		//落下が始まった瞬間のみ実行
		if (prevgravity <= 0 && m_gravity > 0)
		{
			UVRectControl(PlayerAnimeType::Fall);
		}
	}

	//アニメーション
	UVRectControlUpdate();

	//行列
	Math::Matrix mscale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix mtrans= Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = mscale * mtrans;
}

void Player::PostUpdate()
{
	Hit();
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}


void Player::Hit()
{
	//プレイヤー座標調整地面判定用（プレイヤーの足元）
	float groundpossurplusX = 0;
	float groundpossurplusY = 1.8f;

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
			UVRectControl(PlayerAnimeType::Dash);

		}

		//				↓余剰分を反転させる
		m_pos = hitPos -= Math::Vector3(groundpossurplusX, groundpossurplusY, 0);
		m_gravity = 0;
	}

	//球（スフィア）判定地面との当たり判定
	{
		//プレイヤー座標調整壁判定用（プレイヤーの中心）
		float spherepossurplusX = 0;
		float spherepossurplusY = 2.6f;

		//球判定の設定
		KdCollider::SphereInfo sphere;
		sphere.m_sphere.Center = m_pos;
		sphere.m_sphere.Center.y += spherepossurplusY;
		sphere.m_sphere.Center.x += spherepossurplusX;
		sphere.m_sphere.Radius = 0.3f;
		sphere.m_type = KdCollider::TypeGround;

		//デバッグ
		m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

		//球に当たったオブジェクト情報を格納するリスト
		std::list<KdCollider::CollisionResult> retSphereList;

		//全オブジェクトと当たり判定を行う
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			//球と当たり判定
			obj->Intersects(sphere, &retSphereList);
		}

		//球に当たったリストから一番近いオブジェクトを探す
		maxOverLap = 0; //球の時はめりこんだ長さ
		hit = false;
		//当たった方向を格納する変数
		Math::Vector3 hitDir;

		for (auto& ret : retSphereList)
		{
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

void Player::UVRectControl(PlayerAnimeType _type, std::function<void()> _action)
{
	//他のアニメーションが実行中ならジャンプアニメーションを行わない
	if (m_jumppattern != PlayerJumpPattern::None)
	{
		if (m_looppattern != PlayerLoopPattern::None)
		{
			return;
		}
	}

	m_anim = 0;

	//始めに初期化
	m_animid.clear();
	m_action = nullptr;

	float animtime = 0;
	std::vector<int> animid = {};
	int animcnt = 0;


	switch (_type)
	{
	case Player::PlayerAnimeType::Dash:
	
		m_animtime = 30;
		m_animid = m_animidkeep[(int)PlayerAnimeType::Dash];
		m_loopmax = 1;
		break;
	case Player::PlayerAnimeType::Jump:

		m_animtime = 60;

		m_animid =m_animidkeep[(int)PlayerAnimeType::Jump];
		
		//上書きされる前提
		m_loopmax = 999;
		break;
	case Player::PlayerAnimeType::Fall:
	
		m_animtime = 60;

		m_animid =m_animidkeep[(int)PlayerAnimeType::Jump];
		
		//上書きされる前提
		m_loopmax = 999;

		break;
	case Player::PlayerAnimeType::Attack1:
		m_animtime = 60;

		m_animid = m_animidkeep[(int)PlayerAnimeType::Attack1];
		m_loopmax = 1;
		break;
	case Player::PlayerAnimeType::Attack2:
		m_animtime = 60;

		m_animid = m_animidkeep[(int)PlayerAnimeType::Attack2];
		m_loopmax = 1;
		break;
	case Player::PlayerAnimeType::spDash:
		m_animtime = 60;

		m_animid = m_animidkeep[(int)PlayerAnimeType::spDash];
		m_loopmax = 1;

		break;
	default:
		//デフォルトはダッシュ
		m_animtime = 30;
		m_animid = m_animidkeep[(int)PlayerAnimeType::Dash];
		m_loopmax = 1;
		break;
	}

	

	//共通
	m_animmax = m_animid.size();
	m_animcnt = m_loopmax;

	if (_action)
	{
		m_action = _action;
	}

	m_animflg = true;
}

void Player::UVRectControlUpdate()
{
	if (!m_animflg)return;
	if (m_loopmax <= 0)return;

	m_anim += m_animmax / (float)m_animtime;

	if (m_anim >= m_animmax)
	{
		m_animcnt--;

		//animcntが０になるまでループ
		if (m_animcnt <= 0)
		{
			if (m_action)
			{
				m_action();
				m_animflg = false;
				//アニメーション
				UVRectControl(PlayerAnimeType::Dash);
				return;
			}
			else
			{
				m_anim = 0;
				m_animflg = false;
				//アニメーション
				UVRectControl(PlayerAnimeType::Dash);
				return;
			}
		}

		m_anim = 0;

	}

	//アニメーション
	m_polygon->SetUVRect(m_animid[(int)m_anim]);
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

		fgets(dummy, 255, fp);		//1行飛ばす
		fgets(dummy, 255, fp);		//1行飛ばす
		fgets(dummy, 255, fp);		//1行飛ばす

		//アニメーションID読み込み
		for (int i = 0; i < (int)PlayerAnimeType::AnimNum; i++)
		{
			//始めだけ飛ばす
			fscanf_s(fp, "%*[^,]");

			for (int j = 0; j < 20; j++)
			{
				//一個ずつ読み込む
				fscanf_s(fp, ",%d", &animid);

				//もし-1（最後まで読んだ）ならbreak
				if (animid == -1)
				{
					fgets(dummy, 255, fp);		//1行飛ばす
					break;
				}

				//一個ずつ格納
				m_animidkeep[i].push_back(animid);
			}
		}

		fclose(fp);
	}
}

