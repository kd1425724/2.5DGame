#pragma once

class GameGround:public KdGameObject
{
public:
	GameGround() {}
	~GameGround()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:



	std::shared_ptr<KdModelData> m_model;

	Math::Vector3 m_pos = {};

};
