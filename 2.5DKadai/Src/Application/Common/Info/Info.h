#pragma once

class Info
{
public:

	static const int ScrWidth = 1280;
	static const int ScrHeight = 720;

	const float DefaultCameraPosZ = -10.0f;

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
			m_scrollspeed = 0.1f;
		}
		else
		{
			m_scrollspeed = 0;
		}
	}
private:
	//スクロール速度
	float m_scrollspeed = 0.1f;

	//スクロールフラグ
	bool m_scrollflg = true;

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

