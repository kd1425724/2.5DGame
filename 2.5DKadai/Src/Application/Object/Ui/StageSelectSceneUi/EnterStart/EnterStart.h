#pragma once
#include"../../UiBase.h"

class EnterStart:public UiBase
{
public:
	EnterStart() {}
	~EnterStart()override {}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	void SetAsset(const std::string& _filename)override
	{
		std::string path = "Asset/Textures/" + _filename + ".png";
		m_tex = std::make_shared<KdTexture>();
		m_tex->Load(path);
	}

private:

	float m_alpha = 1.0f;
	float m_updownspeed = 0.01f;
};

