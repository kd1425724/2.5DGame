#include "PressEnter.h"

void PressEnter::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/TitleScene/Ui/PressEnter.png");

	Math::Vector3 pos = { 0,-200,0 };
	//行列
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(pos);
	m_mWorld = mtrans;
}

void PressEnter::Update()
{
	//加算
	m_alpha += m_updownspeed;

	//透明度が0.3を下回るか1.0を上回ると反転
	if (m_alpha < 0.1f || m_alpha>1.0f)
	{
		m_updownspeed *= -1;
	}
}

void PressEnter::DrawSprite()
{
	if (!m_tex)return;

	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);

	// 白文字
	Math::Color color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0, nullptr, &color);
	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

