#pragma once

#include"../BaseScene/BaseScene.h"

class ResultSceneUi;

class ResultScene : public BaseScene
{
public :

	ResultScene() {}
	~ResultScene() {}

	void Init()  override;

private :

	void Event() override;

	//UI
	std::shared_ptr<ResultSceneUi> m_resultsceneui;

};
