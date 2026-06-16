#pragma once
#include"../../UiBase.h"
class PressEnter:public UiBase
{
public:
	PressEnter(){}
	~PressEnter()override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

private:

	float m_alpha = 1.0f;
	float m_updownspeed = 0.01f;
};
