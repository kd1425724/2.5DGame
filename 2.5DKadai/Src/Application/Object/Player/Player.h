#pragma once

class Player :public KdGameObject
{
public:
	Player() {}
	~Player()override{}

	void Init();

	void PreUpdate()override;
	void Update()override;
	void PostUpdate() override;

	void DrawLit()override;

	void SetPos(const Math::Vector3& pos) override { m_pos = pos; }

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

	//攻撃パターン管理用
	enum class PlayerAttackPattern
	{
		None,
		Attack1,	//通常攻撃1段目
		Attack2,	//通常攻撃2段目
		Standby		//待機時間中
	};
	PlayerAttackPattern m_attackpattern = PlayerAttackPattern::None;

	static const int StandbyTime = 30;
	int m_standbytime = StandbyTime;
	//2段目攻撃用
	bool m_inputkeep = false;
	
	std::shared_ptr<KdSquarePolygon> m_polygon;

	//座標
	Math::Vector3 m_pos = {};
	//移動ベクトル
	Math::Vector3 m_move = {};
	//移動スピード
	float m_speed = 0;
	//サイズ
	Math::Vector3 m_scale = {};
	//重力
	float m_gravity = 0;
	float m_gravitysubtractionValue = 0.005f;
	//ジャンプ力
	float m_onejumppow = 0.2f;
	float m_twojumppow = 0.15f;

	//地面に着地した瞬間の判定
	bool m_isground = true;

	//アニメーション用
	enum class PlayerAnimeType
	{
		Dash,		//ダッシュ
		Jump,		//ジャンプ
		Fall,		//落下中
		Attack1,	//通常攻撃１段目
		Attack2,	//通常攻撃２段目
		spDash,		//ダッシュ攻撃
		AnimNum		//数
	};
	//現在のアニメーション
	PlayerAnimeType m_nowanimtype=PlayerAnimeType::Dash;

	float m_anim = 0;
	//アニメーション制御用
	//_type			...アニメーションのタイプを指定
	//_action		...必要ならアクションセット
	void UVRectControl(PlayerAnimeType _type,std::function<void()> action = nullptr);
	//アニメーション常時通る
	void UVRectControlUpdate();

	//アニメーション時間
	int m_animtime = 0;
	//アニメーションの最大値
	int m_animmax = 0;
	//アニメーションのid
	std::vector<int> m_animid = {};
	//アニメーションが何回ループするか
	int m_animcnt = 0;
	//アニメーションが終わったらなにをするか
	std::function<void()> m_action = nullptr;
	//アニメーションループ回数保存用
	int m_loopmax = 0;

	//アニメーションフラグ
	bool m_animflg = false;

	//上書き可能かどうかのフラグ
	//ちゃんと設定しないとバグが起きるので注意
	bool m_overwritable = true;

	//アニメーションID保存用
	std::vector<int> m_animidkeep[(int)PlayerAnimeType::AnimNum];
	
};
