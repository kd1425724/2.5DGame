#pragma once
#include"../BaseBackGround.h"
class GameSceneBackGround:public BaseBackGround 
{
public:
	GameSceneBackGround(){}
	~GameSceneBackGround()override{}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;
private:

};
