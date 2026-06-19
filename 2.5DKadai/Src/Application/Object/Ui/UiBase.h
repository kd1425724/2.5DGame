#pragma once

class UiBase:public KdGameObject
{
public:
	UiBase() {}
	~UiBase()override { Release(); }


	void Init()override {}
	void Update()override{}
	void DrawSprite()override;

	void SetAsset(const std::string& texturelname)override
	{
		std::string path = texturelname;

		m_tex = std::make_shared<KdTexture>();
		m_tex = KdAssets::Instance().m_textures.GetData(path);
	}

	//別のオブジェクト情報が必要な時
	virtual void SetObjInfo(std::shared_ptr<KdGameObject> obj) { m_objinfo = obj; }

protected:

	std::shared_ptr<KdTexture> m_tex;

	//別のオブジェクト情報が必要な時
	std::weak_ptr<KdGameObject> m_objinfo;
};

