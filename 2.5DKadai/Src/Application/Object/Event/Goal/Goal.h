#pragma once
#include"../BaseEvent.h"
class Goal :public BaseEvent
{
public:
	Goal(){}
	~Goal()override{}

	void Init()override;
	void OnHit(KdGameObject* _other)override;

	ObjectTag GetObjectTag()override { return ObjectTag::Goal; }

private:

};

