#pragma once

class UiBase:public KdGameObject
{
public:
	UiBase() { Init(); }
	~UiBase()override { Release(); }

	void Update()override{}
	void DrawSprite()override{}

	//別のオブジェクト情報が必要な時
	virtual void SetObjInfo(std::shared_ptr<KdGameObject> obj) { m_objinfo = obj; }

protected:

	void Init()override{}

	//別のオブジェクト情報が必要な時
	std::weak_ptr<KdGameObject> m_objinfo;
};

