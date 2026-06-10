#pragma once

#include"../BaseScene/BaseScene.h"

class StageSelectScene : public BaseScene
{
public:

	StageSelectScene() {}
	~StageSelectScene() {}

	void Init()  override;

private:

	void Event() override;

};
