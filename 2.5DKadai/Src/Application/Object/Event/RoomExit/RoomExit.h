#pragma once
#include"../BaseEvent.h"

class RoomExit:public BaseEvent
{
public:
	RoomExit(){}
	~RoomExit(){}

	void Init()override;
	void OnHit(KdGameObject* _other)override;

	ObjectTag GetObjectTag()override { return ObjectTag::None; }

private:

};

