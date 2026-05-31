#pragma once

class TitleSceneUi:public KdGameObject
{
public:
	TitleSceneUi(){}
	~TitleSceneUi()override{}

private:

	void Init()override;

	void PreUpdate()override;
	void Update() override;
	void PostUpdate()override;

};
