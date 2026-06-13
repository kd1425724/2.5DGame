#pragma once

#include"../BaseScene/BaseScene.h"
class StageSelectSceneUi;

class StageSelectScene : public BaseScene
{
public:

	StageSelectScene() {}
	~StageSelectScene() {}

	void Init()  override;

private:

	void Event() override;

	std::shared_ptr<StageSelectSceneUi> m_stageselectui;


};
