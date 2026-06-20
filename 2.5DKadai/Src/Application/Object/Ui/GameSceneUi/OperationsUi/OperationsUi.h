#pragma once
#include"../../UiBase.h"

class OperationsUi : public UiBase
{
public:

	OperationsUi() {}
	~OperationsUi() override {}

	void Init() override;
	void Update() override;
	void DrawSprite() override;

private:

	//フェード用
	float m_alpha = 1.0f;

	//経過フレーム
	int m_cnt = 0;

	//表示するか
	bool m_drawFlg = true;
};