#pragma once

class RoomObjectBase :public KdGameObject
{
public:
	RoomObjectBase() {}
	~RoomObjectBase()override {}

	void Init()override {}
	void Update()override {}
	void DrawLit()override {}

private:

	std::shared_ptr<KdModelData> m_model;

};
