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

	//スクロール速度セット
	void SetScrollSpeed(const float& _speed = 0.5f) { m_scrollspeed = _speed; }
	//スクロール速度取得
	float GetScrollSpeed() { return m_scrollspeed; }

	//スクロールするかどうかセット
	void SetScrollFlg(const bool& flg)
	{
		m_scrollflg = flg;
		if (m_scrollflg)
		{
			m_scrollspeed = DefaultScrollSpeed;
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

	//スクロールフラグ
	bool m_scrollflg = true;

	//ゴールフラグ
	bool m_goalflg = false;

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

