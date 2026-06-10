#pragma once

class BaseEvent :public KdGameObject
{
public:
	BaseEvent() {}
	~BaseEvent()override {}

	void Init()override {}
	void Update()override;
	
	void OnHit(KdGameObject* _other)override {}

	ObjectTag GetObjectTag()override { return ObjectTag::None; }

private:

};
