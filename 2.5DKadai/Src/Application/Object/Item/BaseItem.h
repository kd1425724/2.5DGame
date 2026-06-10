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

	//Updateをし、行列計算をする場合行列にかける
	//移動行列を返す
	Math::Matrix Scroll();

protected:

	std::shared_ptr<KdModelData> m_model;

private:

};