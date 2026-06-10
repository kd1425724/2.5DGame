#pragma once
#include"../BaseBackGround.h"
class ResultSceneBackGround:public BaseBackGround 
{
public:
	ResultSceneBackGround(){}
	~ResultSceneBackGround()override{}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;
private:

};
