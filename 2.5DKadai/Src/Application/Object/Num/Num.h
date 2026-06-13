#pragma once

class Num:public KdGameObject
{
public:
	Num(){}
	~Num()override{}

	//数字描画設定
	//startpos...一の位
	void SetNumInfo
	(
		UINT _num,
		Math::Vector3 _startpos,
		Math::Vector3 _scale = { 1,1,1 }, 
		Math::Color _color = { 1.0f,1.0f,1.0f,1.0f },
		bool _maxdigitsflg = false, 
		int _maxdigits = 0
	);
	void DrawSprite()override;
private:

	UINT m_num = 0;
	Math::Vector3 m_scale = {1,1,1};
	Math::Color m_color = { 1,1,1,1 };

	bool m_maxdigitsflg = false;
	int m_maxdigits = 0;
};