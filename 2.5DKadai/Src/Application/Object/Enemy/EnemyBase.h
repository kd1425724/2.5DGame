#pragma once

class EnemyBase:public KdGameObject
{
public:
	EnemyBase() {}
	~EnemyBase()override {}

	void Init()override{}
	void Update()override {}
	void DrawLit()override {}

	//座標セット上書き
	void SetPos(const Math::Vector3& pos) override { m_pos = pos; }

protected:
	//Dataロード
	//_filename	...ファイルの名前（敵の名前のみ）
	void DataLoad(std::string _filename);
	
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
	//移動ベクトル
	Math::Vector3 m_move = {};
	//移動スピード
	float m_speed = 0;
	//アニメーション用
	float m_anim = 0;

	//アニメーション制御用
	//enumをintにキャストしてアニメーションtypeを指定する
	virtual void UVRectControl(int _animtype,std::function<void()> _action = nullptr) = 0;
	//アニメーション常時通る
	void UVRectControlUpdate();
	//UVRectControlで共通で行うもの
	//各継承先のUVRectControlの始めによぶ
	void UVRectControlInit();

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
	std::vector<std::vector<int>> m_animidkeep = {};
	//アニメーション終了時共通で行う処理
	std::function<void()> m_commonanimfinishdaction = nullptr;


private:
};
