#pragma once
#include"../../UiBase.h"

enum class StageSelectButtonInfo
{
	Stage1,
	Stage2,
	Back,
	ButtonNum
};

class StageSelectButton:public UiBase
{
public:
	StageSelectButton() { Init(); };
	~StageSelectButton()override { Release(); }


	void Update()override;
	void DrawSprite()override;

	int GetButtonInfo() { return (int)m_button; }

private:

	void Release();

	void Init()override;

	StageSelectButtonInfo m_button = StageSelectButtonInfo::Stage1;

	std::shared_ptr<KdSquarePolygon> m_buttontex[(int)StageSelectButtonInfo::ButtonNum];
	std::shared_ptr<KdSquarePolygon> m_buttonframetex[(int)StageSelectButtonInfo::ButtonNum];
	
};

