#pragma once

class Player :public KdGameObject
{
public:
	Player() {}
	~Player()override
	{
		m_pos = { 100,0,0 };
		//ポイントライト
		KdShaderManager::Instance().WorkAmbientController().AddPointLight
		(
			{ 10,0,0 },							//色
			3,									//半径
			m_pos	//座標
		);
	}

	void Init()override;

	void PreUpdate()override;
	void Update()override;
	void PostUpdate() override;

	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void DrawBright()override;

	ObjectTag GetObjectTag()override { return ObjectTag::Player; }

	//当たり判定だけのプレイヤー生成
	void SetShadowFlg() { m_shadowflg = true; }

private:

	void PlayerDataLoad();

	void Hit();

	//プレイヤーの状態
	enum class PlayerStatePattern
	{
		Start,	//開始時
		Loop,	//ループ
		Death	//死亡時
	};
	//初期パターン設定
	PlayerStatePattern m_statepattern = PlayerStatePattern::Loop;

	//ジャンプ管理用
	enum class PlayerJumpPattern
	{
		None,
		Jump1,		//ジャンプ1段目
		Jump2		//ジャンプ2段目
	};
	PlayerJumpPattern m_jumppattern = PlayerJumpPattern::None;

	
	std::shared_ptr<KdModelData> m_model;
	std::shared_ptr<KdModelData> m_coremodel;

	//移動ベクトル
	Math::Vector3 m_move = {};
	//移動スピード
	float m_speed = 0;
	//サイズ
	Math::Vector3 m_scale = {};
	//重力
	float m_gravity = 0;
	float m_gravitysubtractionvalue = 0.006f;
	//ジャンプ力
	float m_onejumppow = 0.2f;
	float m_twojumppow = 0.18f;

	//地面に着地した瞬間の判定
	bool m_isground = true;	

	//ディゾルブ用
	float m_dissolv = 0;

	//残像用
	struct AfterImage
	{
		Math::Matrix mat;
		float alpha = 1.0f;
		float life = 0.0f;
	};
	std::deque<AfterImage> m_afterImages;

	// 残像制御
	float m_afterImageTimer = 0.0f;
	float m_afterImageInterval = 4; // 基本間隔

	//当たり判定だけのプレイヤー生成フラグ
	bool m_shadowflg = false;

	//ダメージを受けないようにするフラグ
	bool m_damageflg = true;

	int m_dashEffectCnt = 0;
};
