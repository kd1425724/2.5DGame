#pragma once
#include"../../UiBase.h"

class StageSelectButton;

class StageDescription :public UiBase
{
public:
	StageDescription() { Init(); };
	~StageDescription()override { Release(); }

	void DrawSprite()override;

	void SetButton(std::shared_ptr<StageSelectButton> obj) { m_button = obj; }

private:

	void Init()override;

	std::weak_ptr<StageSelectButton> m_button;

	//説明画像
	static const int DescriptionNum = 1;

	std::shared_ptr<KdSquarePolygon> m_descriptionpoly[DescriptionNum];
};

