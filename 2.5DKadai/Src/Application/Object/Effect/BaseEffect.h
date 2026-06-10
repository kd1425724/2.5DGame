#pragma once

class BaseEffect:public KdGameObject
{
public:
	BaseEffect(){}
	~BaseEffect()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	Math::Matrix Scroll();


private:

	Math::Vector3 m_pos = {};

};
