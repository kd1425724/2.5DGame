#include "BlackBack.h"

void BlackBack::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/Common/Back/WhiteBack.png");
}

void BlackBack::DrawSprite()
{
	Math::Color color = { 0,0,0,0.4f };
	//KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0, nullptr, &color);

	//行列初期化
	//KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}
