#pragma once

class BaseItem:public KdGameObject
{
public:
	BaseItem(){}
	~BaseItem()override{}

	void Init()override{}
	void Update()override;
	
	void DrawLit()override {}

	ObjectTag GetObjectTag()override { return ObjectTag::Item; }

	void OnHit(KdGameObject* other)override{}

protected:

	static std::shared_ptr<KdModelData> s_model;
	std::shared_ptr<KdModelData> m_model;

private:

};