#pragma once
#include"../BaseBackGround.h"
class StageSelectSceneBackGround:public BaseBackGround 
{
public:
	StageSelectSceneBackGround(){}
	~StageSelectSceneBackGround()override{}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;
private:

};
