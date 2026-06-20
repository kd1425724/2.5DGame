#include "EnterStart.h"

void EnterStart::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/StageSelectScene/EnterStart/EnterStart.png");
}

void EnterStart::Update()
{
	//加算
	m_alpha += m_updownspeed;

	//透明度が0.3を下回るか1.0を上回ると反転
	if (m_alpha < 0.3f || m_alpha>1.0f)
	{
		m_updownspeed *= -1;
	}
}

void EnterStart::DrawSprite()
{
	if (!m_tex)return;

	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);

	// 白文字
	Math::Color color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0, nullptr, &color);
	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

