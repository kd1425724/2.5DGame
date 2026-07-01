#pragma once

class Info
{
public:
	//px単位画面範囲
	static const int ScrWidth = 1280;
	static const int ScrHeight = 720;

	//カメラのデフォルト値
	const float DefaultCameraPosZ = -10.0f;

	//奈落判定座標
	static const int AbyssJudgmentPos = -7;

	//最後に入ったステージ
	void SetStage(const std::string& stage)
	{
		m_stage = stage;
	}
	std::string GetStage()
	{
		return m_stage;
	}

	//デフォルトスクロール速度取得
	float GetDefaultScrollSpeed()const { return DefaultScrollSpeed; }

	//スクロール速度セット
	void SetScrollSpeed(const float& _speed) 
	{
		m_setscrollspeed = _speed;
		m_scrollspeed = m_setscrollspeed;
	}
	//スクロール速度取得
	float GetScrollSpeed() { return m_scrollspeed; }

	bool GetScrollFlg() { return m_scrollflg; }

	//スクロールするかどうかセット
	void SetScrollFlg(const bool& flg)
	{
		m_scrollflg = flg;
		if (m_scrollflg)
		{
			m_scrollspeed = m_setscrollspeed;
		}
		else
		{
			m_scrollspeed = 0;
		}
	}

	//ゴールフラグ取得
	bool GetGoalFlg()const { return m_goalflg; }

	//ゴールフラグセット
	void SetGoalFlg(const bool& flg) { m_goalflg = flg; }

	//部屋の間隔
	Math::Vector3 GetRoomSpacing()const { return { 21,0,0 }; }
	

private:
	float DefaultScrollSpeed = 0.2f;
	//スクロール速度
	float m_scrollspeed = DefaultScrollSpeed;
	//スクロール速度設定用
	float m_setscrollspeed = 0;


	//スクロールフラグ
	bool m_scrollflg = true;

	//ゴールフラグ
	bool m_goalflg = false;

	std::string m_stage = "";

private:
	Info(){}
	~Info(){}

public:

	static Info& Instance()
	{
		static Info instance;
		return instance;
	}
};

#define INFO Info::Instance()

