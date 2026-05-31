#pragma once

class EnemyBase:public KdGameObject
{
public:
	EnemyBase() {}
	~EnemyBase()override {}

	void Update()override {};
	void DrawLit()override {};

protected:

	void Init()override{}

	//敵の状態
	enum class EnemyStatePattern
	{
		Start,	//開始時
		Loop,	//ループ
		Death	//死亡時
	};

	EnemyStatePattern m_statepattern = EnemyStatePattern::Start;

	//画像
	std::shared_ptr<KdSquarePolygon> m_polygon = nullptr;
	//座標
	Math::Vector3 m_pos = {};
	//移動スピード
	float m_speed = 0;
	//アニメーション用
	float m_anim = 0;

	//アニメーション制御用
	//animtime  ...アニメーションの時間
	//anim		...アニメーション番号指定（{24,25,24,26}など）
	//animcnt   ...アニメーションが何回ループするか
	//action    ...アニメーションが終了したらなにをするか（）
	void UVRectControl(int _animtime, std::vector<int> _animid,int _animcnt, std::function<void()> action);
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

private:
};
