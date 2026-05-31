#pragma once

#include"../BaseScene/BaseScene.h"

class StageSelectScene : public BaseScene
{
public:

	StageSelectScene() { Init(); }
	~StageSelectScene() {}

private:

	void Event() override;
	void Init()  override;
};
