#pragma once
#include"../BaseBackGround.h"

class TitleSceneBackGround:public BaseBackGround 
{
public:
	TitleSceneBackGround(){}
	~TitleSceneBackGround()override{}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;
private:

};
