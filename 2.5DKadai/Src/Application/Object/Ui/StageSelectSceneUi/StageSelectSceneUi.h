#pragma once

class StageSelectSceneUi :public KdGameObject
{
public:
	StageSelectSceneUi() { Init(); }
	~StageSelectSceneUi()override {}

	void Init()override;
	void PreUpdate()override;
	void Update() override;
	void PostUpdate()override;

	void DrawSprite()override;

private:


	
};
