#pragma once

#include"../BaseScene/BaseScene.h"

class TitleSceneUi;

class TitleScene : public BaseScene
{
public :

	TitleScene()  { }
	~TitleScene() {}

	void Init()  override;

private :

	void Event() override;

	std::shared_ptr<TitleSceneUi> m_titlesceneui;
};
