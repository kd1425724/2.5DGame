#pragma once

class BaseBackGround:public KdGameObject
{
public:
	BaseBackGround(){}
	~BaseBackGround()override{}

	void Init()override;
	void Update()override{}
	void DrawUnLit()override;

protected:
	std::shared_ptr<KdSquarePolygon> m_polygon;

private:

	

};

