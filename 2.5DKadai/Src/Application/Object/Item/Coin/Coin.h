#pragma once
#include"../BaseItem.h"

class Coin:public BaseItem
{
public:
	Coin(){}
	~Coin(){}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

	void OnHit(KdGameObject* other)override;

private:
};