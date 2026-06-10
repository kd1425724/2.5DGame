#include "PressAny.h"

void PressAny::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/");

	//行列
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mWorld = mtrans;
}

void PressAny::Update()
{
	//加算
	m_alpha += m_updownspeed;

	//透明度が0.3を下回るか1.0を上回ると反転
	if (m_alpha < 0.3f || m_alpha>1.0f)
	{
		m_updownspeed *= -1;
	}
}

void PressAny::DrawSprite()
{
	if (!m_tex)return;

	Math::Color color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0, nullptr, &color);
}
